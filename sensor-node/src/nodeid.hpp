
#pragma once



class NodeId
{

public:
   NodeId();

   const char* get();
   void set(const char* node_id);
   
private:
   uint16_t eeprom_crc16_(size_t len);
   
   static const int node_name_len_ = 5;
   char name_[node_name_len_ + 1];
};




