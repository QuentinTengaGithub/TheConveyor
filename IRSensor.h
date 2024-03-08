int last_recv_value = 0;
int cur_recv_value  = 0;
 
 
bool irSensor(){
  cur_recv_value = digitalRead(36);
  Serial.println(cur_recv_value);

  return (last_recv_value != cur_recv_value);
}

