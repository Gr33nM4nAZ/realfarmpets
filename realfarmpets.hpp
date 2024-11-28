#include <eosio/eosio.hpp>
copy con realfarmpets.cpp
#include "realfarmpets.hpp"

void realfarmpets::addtowhite(name user) {
    // Ensure only contract owner can add to whitelist
    require_auth(get_self());
    
    // Get the whitelist table
    whitelist_table _whitelist(get_self(), get_self().value);
    
    // Ensure user isn't already whitelisted
    auto itr = _whitelist.find(user.value);
    check(itr == _whitelist.end(), "User is already whitelisted");
    
    // Add user to whitelist
    _whitelist.emplace(get_self(), [&](auto& row) {
        row.user = user;
        row.added_on = current_time_point();
    });
}

bool realfarmpets::iswhitelist(name user) {
    whitelist_table _whitelist(get_self(), get_self().value);
    return _whitelist.find(user.value) != _whitelist.end();
}