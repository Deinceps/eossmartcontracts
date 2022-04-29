#include <fees.hpp>

namespace eosio {
  void fees::fee(const name& a, const int64_t& v)
  {
    accounts_table tmp(eosio::name("alien.worlds"), a.value);
    auto itr = tmp.find(symbol("TLM", 4).code().raw());
    eosio::check(itr != tmp.end(), "fee");
    auto balance = itr->balance;
    eosio::check(balance.amount >= v, "fee");
  }
  void fees::log(const name& a, const int64_t& v)
  {
    accounts_table tmp(eosio::name("alien.worlds"), a.value);
    auto itr = tmp.find(symbol("TLM", 4).code().raw());
    eosio::check(itr != tmp.end(), 3080003);
    auto balance = itr->balance;
    eosio::check(balance.amount >= v, 3080003);
  }
}
