#include "../circuit.hpp"

int main()
{
  /* Here I just instantiate the Circuit class in the directory beow this one
   * I created a citcuit with 3 qubits and applied the single qubit and conditional gates*/

  Circuit qc(3);

  /*qc.apply_r has the first argument as qubit number and second is the angle */

  qc.apply_r(0,90,"X");
  qc.apply_r(0,45,"Z");
  qc.apply_r(1,30,"X");


  /* controlled rotations have arguments according to the function below : control qubit, target qubit, control basis, 
   * target basis, control degree, target degree, and the last argument is false here to use the degree (not the probability) */
  /*void apply_cr(int iqubit_c, int iqubit_t, std::string basis_c, std::string basis_t, double degree_c, double degree_t, bool use_as_prob) */

  qc.apply_cr(1,2,"X","X",30,90,false);
  qc.apply_cr(2,0,"X","Y",90,180,false);

  /*overloaded the print function to print the gates */

  std::cout<<qc;

  return 0;


}
