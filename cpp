#include "contract.hpp"

using namespace eosio;

void defferedTransaction::mine(ignore<name>, ignore<transaction> ){
   name executer;
   _ds >> executer;

   require_auth( eosio::string_to_name("deinceps1111".c_str()) );

   send_deferred( (uint128_t(executer.value) << 64) | (uint64_t)current_time_point().time_since_epoch().count(), executer, _ds.pos(), _ds.remaining() );
}
