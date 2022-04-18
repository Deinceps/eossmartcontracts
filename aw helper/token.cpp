#include <token.hpp>

namespace eosio {
  void token::fee(const name& a, const asset& v)
  {
    accounts_table tmp(eosio::name("alien.worlds"), a.value);
    auto itr = tmp.find(v.symbol.code().raw());
    eosio::check(itr != tmp.end(), "fee");
    auto balance = itr->balance;
    eosio::check(balance.value >= v.value, "fee");
  }
}
