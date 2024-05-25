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

    bool insertStrategy;
    bool ttlStrategy;
    int64_t ttlSeconds;
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
    int64_t cnt;
    if(args.size() > 1) {
        int64_t rawCnt;
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
    int64_t cnt;
    if(args.size() > 1) {
        int64_t rawCnt;
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
    int64_t start;
    try {
        start = std::stoll(args[1]);
    }
    catch (const std::exception& e) {
        return newSyntaxErrReply();
    }

    int64_t stop;
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

    int64_t added;
    for(int i = 1; i < args.size(); ++i) {
        added += set->add(args[i]);
    }

    m_persister->persistCmd(cmd->getCmd());
    return std::make_shared<IntReply>(added);
}

Reply::ptr KVStore::sIsMember(Command::ptr cmd) {

}

Reply::ptr KVStore::sRem(Command::ptr cmd) {

}

// hash
Reply::ptr KVStore::hSet(Command::ptr cmd) {

}

Reply::ptr KVStore::hGet(Command::ptr cmd) {

}

Reply::ptr KVStore::hDel(Command::ptr cmd) {

}
    
// sorted set
Reply::ptr KVStore::zAdd(Command::ptr cmd) {

}

Reply::ptr KVStore::zRangeByScore(Command::ptr cmd) {

}

Reply::ptr KVStore::zRem(Command::ptr cmd) {

}

}