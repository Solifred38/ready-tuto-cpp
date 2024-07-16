#pragma once

#define GMAP_DEFINE(Var, Key, Value, ...) \
std::map<Key, Value> GMAP_DATA_##Var = { \
    __VA_ARGS__ \
}; \
\
Value GMAP_GET_VALUE_##Var(Key _key) { \
    Value lValue; \
    std::map<Key, Value>::iterator it = std::find_if(GMAP_DATA_##Var.begin() \
    , GMAP_DATA_##Var.end(), [&](const std::pair<Key, Value>& _pair) { \
        return _pair.first == _key; \
    }); \
    if(it != GMAP_DATA_##Var.end()) { \
        lValue = it->second; \
    }; \
    return lValue; \
} \
\
Key GMAP_GET_KEY_##Var(Value _value) { \
    Key lKey; \
    std::map<Key, Value>::iterator it = std::find_if(GMAP_DATA_##Var.begin() \
    , GMAP_DATA_##Var.end(), [&](const std::pair<Key, Value>& _pair) { \
        return _pair.second == _value; \
    }); \
    if(it != GMAP_DATA_##Var.end()) { \
        lKey = it->first; \
    }; \
    return lKey; \
} \
\
bool GMAP_EXIST_VALUE_##Var(Value _value) { \
    std::map<Key, Value>::iterator it = std::find_if(GMAP_DATA_##Var.begin() \
    , GMAP_DATA_##Var.end(), [&](const std::pair<Key, Value>& _pair) { \
        return _pair.second == _value; \
    }); \
    return (it != GMAP_DATA_##Var.end()); \
} \
\
bool GMAP_EXIST_KEY_##Var(Key _key) { \
    std::map<Key, Value>::iterator it = std::find_if(GMAP_DATA_##Var.begin() \
    , GMAP_DATA_##Var.end(), [&](const std::pair<Key, Value>& _pair) { \
        return _pair.first == _key; \
    }); \
    return (it != GMAP_DATA_##Var.end()); \
}

#define GMAP_GET_VALUE(Var, Key) \
GMAP_GET_VALUE_##Var(Key)

#define GMAP_GET_KEY(Var, Value) \
GMAP_GET_KEY_##Var(Value)

#define GMAP_EXIST_VALUE(Var, Key) \
GMAP_EXIST_VALUE_##Var(Key)

#define GMAP_EXIST_KEY(Var, Value) \
GMAP_EXIST_KEY_##Var(Value)
