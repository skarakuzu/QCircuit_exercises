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
   * target basis, control degree, target degree, and the last argument is false here to use the probability to make decision 
   * Unfortunately, I could not have time to imlpement the random number generation according to some probability distribution */

  /*void apply_cr(int iqubit_c, int iqubit_t, std::string basis_c, std::string basis_t, double degree_c, double degree_t, bool use_as_prob) */

  qc.apply_cr(1,2,"X","X",30,90,false);
  qc.apply_cr(2,0,"X","Y",90,180,false);

  /* generating 4 random single qubit rotations with random qubits, angles and degrees*/

  double angle0= qc.get_rndn_degree();  
  int qbt0 = qc.get_rndn_qubit();
  std::string basis0 = qc.get_rndn_basis();

  double angle1= qc.get_rndn_degree();  
  int qbt1 = qc.get_rndn_qubit();
  std::string basis1 = qc.get_rndn_basis();

  double angle2= qc.get_rndn_degree();  
  int qbt2 = qc.get_rndn_qubit();
  std::string basis2 = qc.get_rndn_basis();
  
  double angle3= qc.get_rndn_degree();  
  int qbt3 = qc.get_rndn_qubit();
  std::string basis3 = qc.get_rndn_basis();

  std::cout<<"random rotations qubit, angle, basis : "<<qbt0<<" "<<angle0<<" "<<basis0<<std::endl;
  std::cout<<"random rotations qubit, angle, basis : "<<qbt1<<" "<<angle1<<" "<<basis1<<std::endl;
  std::cout<<"random rotations qubit, angle, basis : "<<qbt2<<" "<<angle2<<" "<<basis2<<std::endl;
  std::cout<<"random rotations qubit, angle, basis : "<<qbt3<<" "<<angle3<<" "<<basis3<<std::endl;


  qc.apply_r(qbt0,angle0,basis0);
  qc.apply_r(qbt1,angle1,basis1);
  qc.apply_r(qbt2,angle2,basis2);
  qc.apply_r(qbt3,angle3,basis3);

  /*genetaring two random conditionals , assuming that the control geree is 30 and control basis is "X" 
   * since the pdf function is not implemented*/

  double angle_t0 = qc.get_rndn_degree();
  int qbt_t0 = qc.get_rndn_qubit();
  int qbt_c0 = qc.get_rndn_qubit();
  std::string basis_t0 = qc.get_rndn_basis();
  
  double angle_t1 = qc.get_rndn_degree();
  int qbt_t1 = qc.get_rndn_qubit();
  int qbt_c1 = qc.get_rndn_qubit();
  std::string basis_t1 = qc.get_rndn_basis();

  std::cout<<"random conditionals qubit_c, qubit_t, basis_t : "<<qbt_c0<<" "<<qbt_t0<<" "<<angle_t0<<" "<<basis_t0<<std::endl;
  std::cout<<"random conditionals qubit_c, qubit_t, basis_t : "<<qbt_c1<<" "<<qbt_t1<<" "<<angle_t1<<" "<<basis_t1<<std::endl;

  qc.apply_cr(qbt_c0,qbt_t0,"X",basis_t0,30,angle_t0,false);
  qc.apply_cr(qbt_c1,qbt_t1,"X",basis_t1,30,angle_t1,false);


  /*overloaded the print function to print the gates */

  std::cout<<qc;

  return 0;


}
