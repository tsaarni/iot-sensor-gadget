
#pragma once



class NodeId
{

public:
   NodeId();

   const char* get();
   void set(const char* node_id);
   
private:
   uint16_t eeprom_crc16_(size_t len);
   
   static const int node_id_len_ = 5;
   char node_[node_id_len_ + 1];
};




