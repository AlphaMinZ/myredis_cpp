#include "kv_store.h"
#include "../handler/reply.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

namespace alphaMin {

// Reply::ptr KVStore::expire(Command::ptr cmd) {
//     auto args = cmd->getArgs();
//     auto key = args[0];

//     int64_t ttl;
//     try {
//         ttl = std::stoll(args[1]);
//     }
//     catch (const std::exception& e) {
//         return newSyntaxErrReply();
//     }
    
//     if(ttl <= 0) {
//         return std::make_shared<ErrReply>("ERR invalid expire time");
//     }

//     auto expireAt = GetCurrentMS() + ttl;
//     std::vector<std::string> _cmd;
//     _cmd.push_back(CmdTypeExpireAt);
//     _cmd.push_back(key);
//     // _cmd.push_back()
    
// }

// Reply::ptr KVStore::expireAt(Command::ptr) {

// }

// string
Reply::ptr KVStore::get(Command::ptr cmd) {
    auto args = cmd->getArgs();
    auto key = args[0];
    auto v = getAsString(key);
    if(v.get() == nullptr) {
        return newNillReply();
    }
    return std::make_shared<BulkReply>(v);
}

Reply::ptr KVStore::mGet(Command::ptr cmd) {
    auto args = cmd->getArgs();
    std::vector<std::string> res;
    res.reserve(args.size());

    for(auto& arg : args) {
        auto v = getAsString(arg);
        if(v.get() == nullptr) {
            res.push_back("(nil)");
            continue;
        }
        res.push_back(v->toString());
    }

    return std::make_shared<MultiBulkReply>(res);
}

static std::string toLower(const std::string& str) {
    std::string result = str;

    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    return result;
}

Reply::ptr KVStore::set(Command::ptr cmd) {
    auto args = cmd->getArgs();
    auto key = args[0];
    auto value = args[1];

    bool insertStrategy = false;
    bool ttlStrategy = false;
    int64_t ttlSeconds = 0;
    auto ttlIndex = -1;

    for(int i = 2; i < args.size(); ++i) {
        auto flag = toLower(args[i]);
        if(std::strcmp(flag.c_str(), "nx") == 0) {
            insertStrategy = true;
        } else if(std::strcmp(flag.c_str(), "ex") == 0) {
            if(ttlStrategy) {
                return newSyntaxErrReply();
            }
            if(i == (args.size() - 1)) {
                return newSyntaxErrReply();
            }
            int64_t ttl;
            try {
                ttl = std::stoll(args[1]);
            }
            catch (const std::exception& e) {
                return newSyntaxErrReply();
            }
            if(ttl <= 0) {
                std::make_shared<ErrReply>("ERR invalid expire time");
            }

            ttlStrategy = true;
            ttlSeconds = ttl;
            ttlIndex = i;
            ++i;
        } else {
            return newSyntaxErrReply();
        }
    }

    // 将 args 剔除 ex 部分，进行持久化
    if(ttlIndex != -1) {
        args.erase(args.begin() + ttlIndex, args.begin() + ttlIndex + 2);
    }

    // 设置
    auto affected = put(key, value, insertStrategy);
    if(affected > 0 && ttlStrategy) {
        // TODO
    }

    // 过期时间处理
    if(affected > 0) {
        std::vector<std::string> tmp;
        tmp.push_back(CmdTypeSet);
        tmp.insert(tmp.end(), args.begin(), args.end());
        m_persister->persistCmd(tmp);
        return std::make_shared<IntReply>(affected);
    }

    return newNillReply();
}

Reply::ptr KVStore::mSet(Command::ptr cmd) {
    auto args = cmd->getArgs();
    if((args.size() & 1) == 1) {
        return newSyntaxErrReply();
    }

    for(int i = 0; i < args.size(); i += 2) {
        put(args[i], args[i+1], false);
    }

    m_persister->persistCmd(cmd->getCmd());
    return std::make_shared<IntReply>(((int64_t)(args.size())) >> 1);
}

// list
Reply::ptr KVStore::lPush(Command::ptr cmd) {
    auto args = cmd->getArgs();
    auto key = args[0];
    auto list = getAsList(key);

    if(list.get() == nullptr) {
        list = std::make_shared<listEntity>(key);
        putAsList(key, list);
    }

    for(int i = 1; i < args.size(); ++i) {
        list->lPush(args[i]);
    }

    m_persister->persistCmd(cmd->getCmd());
    return std::make_shared<IntReply>(list->len());
}

Reply::ptr KVStore::lPop(Command::ptr cmd) {
    auto args = cmd->getArgs();
    auto key = args[0];
    int64_t cnt = 0;
    if(args.size() > 1) {
        int64_t rawCnt = 0;
        try {
            rawCnt = std::stoll(args[1]);
        }
        catch (const std::exception& e) {
            return newSyntaxErrReply();
        }
        if(rawCnt < 1) {
            return newSyntaxErrReply();
        }
        cnt = rawCnt;
    }

    auto list = getAsList(key);
    if(list.get() == nullptr) {
        return newNillReply();
    }

    if(cnt == 0) {
        cnt = 1;
    }

    auto poped = list->lPop(cnt);
    if(poped.size() == 0) {
        return newNillReply();
    }

    m_persister->persistCmd(cmd->getCmd());

    if(poped.size() == 1) {
        return std::make_shared<BulkReply>(poped[0]);
    }

    return std::make_shared<MultiBulkReply>(poped);
}

Reply::ptr KVStore::rPush(Command::ptr cmd) {
    auto args = cmd->getArgs();
    auto key = args[0];
    auto list = getAsList(key);

    if(list.get() == nullptr) {
        list = std::make_shared<listEntity>(key);
        putAsList(key, list);
    }

    for(int i = 1; i < args.size(); ++i) {
        list->rPush(args[i]);
    }

    m_persister->persistCmd(cmd->getCmd());
    return std::make_shared<IntReply>(list->len());
}

Reply::ptr KVStore::rPop(Command::ptr cmd) {
    auto args = cmd->getArgs();
    auto key = args[0];
    int64_t cnt = 0;
    if(args.size() > 1) {
        int64_t rawCnt = 0;
        try {
            rawCnt = std::stoll(args[1]);
        }
        catch (const std::exception& e) {
            return newSyntaxErrReply();
        }
        if(rawCnt < 1) {
            return newSyntaxErrReply();
        }
        cnt = rawCnt;
    }

    auto list = getAsList(key);
    if(list.get() == nullptr) {
        return newNillReply();
    }

    if(cnt == 0) {
        cnt = 1;
    }

    auto poped = list->rPop(cnt);
    if(poped.size() == 0) {
        return newNillReply();
    }

    m_persister->persistCmd(cmd->getCmd());

    if(poped.size() == 1) {
        return std::make_shared<BulkReply>(poped[0]);
    }

    return std::make_shared<MultiBulkReply>(poped);
}

Reply::ptr KVStore::lRange(Command::ptr cmd) {
    auto args = cmd->getArgs();
    if(args.size() != 3) {
        return newSyntaxErrReply();
    }

    auto key = args[0];
    int64_t start = 0;
    try {
        start = std::stoll(args[1]);
    }
    catch (const std::exception& e) {
        return newSyntaxErrReply();
    }

    int64_t stop = 0;
    try {
        stop = std::stoll(args[2]);
    }
    catch (const std::exception& e) {
        return newSyntaxErrReply();
    }

    auto list = getAsList(key);
    if(list.get() == nullptr) {
        return newNillReply();
    }

    auto got = list->range(start, stop);
    if(got.size() != 0) {
        return std::make_shared<MultiBulkReply>(got);
    }

    return newNillReply();
}

// set
Reply::ptr KVStore::sAdd(Command::ptr cmd) {
    auto args = cmd->getArgs();
    auto key = args[0];
    auto set = getAsSet(key);

    if(set.get() == nullptr) {
        set = std::make_shared<setEntity>(key);
        putAsSet(key, set);
    }

    int64_t added = 0;
    for(int i = 1; i < args.size(); ++i) {
        added += set->add(args[i]);
    }

    m_persister->persistCmd(cmd->getCmd());
    return std::make_shared<IntReply>(added);
}

Reply::ptr KVStore::sIsMember(Command::ptr cmd) {
    auto args = cmd->getArgs();
    if(args.size() != 2) {
        return newSyntaxErrReply();
    }

    auto key = args[0];
    auto set = getAsSet(key);
    
    if(set.get() == nullptr) {
        return std::make_shared<IntReply>(0);
    }

    return std::make_shared<IntReply>(set->exist(args[1]));
}

Reply::ptr KVStore::sRem(Command::ptr cmd) {
    auto args = cmd->getArgs();
    auto key = args[0];
    auto set = getAsSet(key);

    if(set.get() == nullptr) {
        return std::make_shared<IntReply>(0);
    }

    int64_t remed = 0;
    for(int i = 1; i < args.size(); ++i) {
        remed += set->rem(args[i]);
    }

    if(remed > 0) {
        m_persister->persistCmd(cmd->getCmd());
    }

    return std::make_shared<IntReply>(remed);
}

// hash
Reply::ptr KVStore::hSet(Command::ptr cmd) {
    auto args = cmd->getArgs();
    if(((args.size()) & 1) != 1) {
        return newSyntaxErrReply();
    }

    auto key = args[0];
    auto hmap = getAsHashMap(key);

    if(hmap.get() == nullptr) {
        hmap = std::make_shared<hashMapEntity>(key);
        putAsHashMap(key, hmap);
    }

    for(int i = 0; i < args.size() - 1; i += 2) {
        auto hkey = args[i + 1];
        auto hvalue = args[i + 2];
        hmap->put(hkey, hvalue);
    }

    m_persister->persistCmd(cmd->getCmd());
    return std::make_shared<IntReply>((int64_t)((args.size() - 1) >> 1));
}

Reply::ptr KVStore::hGet(Command::ptr cmd) {
    auto args = cmd->getArgs();
    auto key = args[0];
    auto hmap = getAsHashMap(key);    

    if(hmap.get() == nullptr) {
        return newNillReply();
    }

    auto v = hmap->get(args[1]);
    if(v.size() != 0) {
        return std::make_shared<BulkReply>(v);
    }

    return newNillReply();
}

Reply::ptr KVStore::hDel(Command::ptr cmd) {
    auto args = cmd->getArgs();
    auto key = args[0];
    auto hmap = getAsHashMap(key); 

    if(hmap.get() == nullptr) {
        return std::make_shared<IntReply>(0);
    }

    int64_t remed = 0;
    for(int i = 1; i < args.size(); ++i) {
        remed += hmap->del(args[i]);
    }

    if(remed > 0) {
        m_persister->persistCmd(cmd->getCmd());
    }
    return std::make_shared<IntReply>(remed);
}
    
// sorted set
Reply::ptr KVStore::zAdd(Command::ptr cmd) {
    auto args = cmd->getArgs();
    if(((args.size()) & 1) != 1) {
        return newSyntaxErrReply();
    }

    auto key = args[0];
    std::vector<int64_t> scores;
    scores.reserve((args.size() - 1) >> 1);
    std::vector<std::string> members;
    members.reserve((args.size() - 1) >> 1);

    for(int i = 0; i < args.size() - 1; i += 2) {
        int64_t score = 0;
        try {
            score = std::stoll(args[i + 1]);
        }
        catch (const std::exception& e) {
            return newSyntaxErrReply();
        }

        scores.push_back(score);
        members.push_back(args[i + 2]);
    }

    auto zset = getAsSortedSet(key);

    if(zset.get() == nullptr) {
        zset = std::make_shared<skiplist>(key);
        putAsSortedSet(key, zset);
    }

    for(int i = 0; i < scores.size(); ++i) {
        zset->add(scores[i], members[i]);
    }

    m_persister->persistCmd(cmd->getCmd());
    return std::make_shared<IntReply>((int64_t)(scores.size()));
}

Reply::ptr KVStore::zRangeByScore(Command::ptr cmd) {
    auto args = cmd->getArgs();
    if(args.size() < 3) {
        return newSyntaxErrReply();
    }

    auto key = args[0];
    int64_t score1 = 0;
    int64_t score2 = 0;
    try {
        score1 = std::stoll(args[1]);
        score2 = std::stoll(args[2]);
    }
    catch (const std::exception& e) {
        return newSyntaxErrReply();
    }
    
    auto zset = getAsSortedSet(key);

    if(zset.get() == nullptr) {
        return newNillReply();
    } 

    auto rawRes = zset->range(score1, score2);
    if(rawRes.size() == 0) {
        return newNillReply();
    }

    std::vector<std::string> res;
    res.reserve(rawRes.size());
    for(auto& item : rawRes) {
        res.push_back(item);
    }

    return std::make_shared<MultiBulkReply>(res);
}

Reply::ptr KVStore::zRem(Command::ptr cmd) {
    auto args = cmd->getArgs();
    auto key = args[0];
    auto zset = getAsSortedSet(key);

    if(zset.get() == nullptr) {
        return std::make_shared<IntReply>(0);
    }

    int64_t remed = 0;
    for(auto& arg : args) {
        remed += zset->rem(arg);
    }

    if(remed > 0) {
        m_persister->persistCmd(cmd->getCmd());
    }
    return std::make_shared<IntReply>(remed);
}

}