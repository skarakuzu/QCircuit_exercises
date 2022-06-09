#include "../circuit.hpp"

int main()
{

  Circuit qc(3);

  qc.apply_rx(0,90);
  qc.apply_rz(0,45);
  qc.apply_rx(1,35);

  qc.apply_cr(1,2,"X","X",30,90,true);
  qc.apply_cr(2,0,"X","Y",90,180,true);

  std::cout<<qc;

  return 0;


}