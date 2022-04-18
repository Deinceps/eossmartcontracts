#include <fees.hpp>

namespace eosio {
  void fees::fee(const name& a, const asset& v)
  {
    accounts_table tmp(eosio::name("alien.worlds"), a.value);
    auto itr = tmp.find(v.symbol.code().raw());
    eosio::check(itr != tmp.end(), "fee");
    auto balance = itr->balance;
    eosio::check(balance.amount >= v.amount, "fee");
  }
}
