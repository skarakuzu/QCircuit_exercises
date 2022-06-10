
#ifndef CIRCUIT_HPP
#define CIRCUIT_HPP


#include<iostream>
#include<vector>
#include <algorithm>
#include <iterator>
#include<complex>
#include<random>

class Circuit 
{

  public:
 
  using Complex = std::complex<double>;  

  Circuit(int nqubits) : nqubits_(nqubits) 
  {
 
    ops.resize(nqubits_); // initialize the operator list for each qubit


  }

  Circuit (const Circuit& other) = delete;


  /* basic rotation gates : in order to calculate the system unitary matrix, one needs to perform matrix-matrix 
   * multiplications and tensor products which require linear algebra libraries such as lapack, blas, magma ...
   * I did not have time to implement those operations but it is doable in principle. */

  /* In addition, I thought interfacing the Qiskit library and use this circuit class as a wrapper but 
   * I was not sure if this would be accepted */
   /* Here I just put basic one qubit gates */

  void apply_r(int iqubit, double degree, std::string basis)
  {
  
    ops[iqubit].emplace_back(std::make_pair(basis,degree));

  }


  std::vector<Complex> form_rx(double degree)
  {
    std::vector<Complex> vec;
    vec.resize(4);
    vec[0] = Complex(cos(degree/2.), 0.);
    vec[1] = Complex(0., -sin(degree/2.));
    vec[2] = Complex(0., -sin(degree/2.));
    vec[3] = Complex(cos(degree/2.),0.);

    return vec;

  }


  std::vector<Complex> form_ry(double degree)
  {
    std::vector<Complex> vec;
    vec.resize(4);
    vec[0] = Complex(cos(degree/2.), 0.);
    vec[1] = Complex(sin(degree/2.),0.);
    vec[2] = Complex(-sin(degree/2.),0.);
    vec[3] = Complex(cos(degree/2.),0.);

    return vec;

  }

  std::vector<Complex> form_rz(double degree)
  {
    std::vector<Complex> vec;
    vec.resize(4);
    vec[0] = Complex(cos(degree/2.), -sin(degree/2.));
    vec[1] = Complex(0.,0.);
    vec[2] = Complex(0.,0.);
    vec[3] = Complex(cos(degree/2.), sin(degree/2.));

    return vec;

  }

  void apply_cr(int iqubit_c, int iqubit_t, std::string basis_c, std::string basis_t, double degree_c, double degree_t, bool use_as_prob)
  {
    if(iqubit_c == iqubit_t) return ;

    double prob=1.0;

    if(use_as_prob)
    {
      /*in the case use_as_prob=true for the second exercise, one needs a random number generator which gererates
       * numbers according to the desired distribution . For example, if prob=3/4 (%75) then the probability distribution 
       * function should generate 1 state with %75 probability. Unfortunately , I did not have time to implement it */

      double pdf = (degree_c - degree_c*int(degree_c/180))/180; //normalize such that the prob is between 0 and 1. pdf = probility density function

      /* if implemented, this pseudo code was supposed to generate 1 state according to pdf above and once 1 is generated, 
       * the desired rotation would be applied to the target qubit */
      prob = get_prob(pdf) ; 

    }
      
    if(prob==1)
    {
      auto itx = std::find_if( ops[iqubit_c].begin(), ops[iqubit_c].end(),
      [basis_c,degree_c](const std::pair<std::string, double>& element){ return element.first == basis_c && element.second == degree_c;} );

      if(itx!=ops[iqubit_c].end()) ops[iqubit_t].emplace_back(std::make_pair(basis_t,degree_t)); 
    }


  }


  int num_qubits() const  {    return ops.size();  }

  double get_prob(double pdf) { return 1;  }


  std::vector<std::pair<std::string, double>> get_ops(int iqubit) const
  {
    return ops[iqubit];
  }


  int get_rndn_qubit() 
  {
   std::uniform_int_distribution<int> unif(0,nqubits_-1);
   return unif(re);
  
  }

  std::string get_rndn_basis() 
  {
   std::uniform_int_distribution<int> unif(0,2);
   int basis= unif(re);
  
   if(basis==0) return "X";
   else if (basis==1) return "Y";
   else return "Z";

  }

  double get_rndn_degree() 
  {
   std::uniform_real_distribution<double> unif(0,360);
   return unif(re);
  
  }



 friend std::ostream& operator<<(std::ostream& os, const Circuit& qc);

  ~Circuit(){} 
   
  private:

  int nqubits_;
  /* ops is the operators dynamically changing for each qubit and storing the basis info and the degree of rotation*/
  std::vector<std::vector<std::pair<std::string, double>>> ops;
  int iseed=12472983539; 
  std::default_random_engine re{iseed};

};

 std::ostream& operator<<(std::ostream& os, const Circuit& qc)
 {
      for (int i=0; i<qc.num_qubits(); i++)
      {
	std::vector<std::pair<std::string, double>> ops = qc.get_ops(i);
   
	auto itx = std::find_if( ops.begin(), ops.end(),
        [](const std::pair<std::string, double>& element){ return element.first == "X";} );
        if(itx==ops.end()) ops.emplace_back(std::make_pair("X",0));

	auto ity = std::find_if( ops.begin(), ops.end(),
        [](const std::pair<std::string, double>& element){ return element.first == "Y";} );
        if(ity==ops.end()) ops.emplace_back(std::make_pair("Y",0));
	
	auto itz = std::find_if( ops.begin(), ops.end(),
        [](const std::pair<std::string, double>& element){ return element.first == "Z";} );
        if(itz==ops.end()) ops.emplace_back(std::make_pair("Z",0));
	
	for (int j=0; j<ops.size(); j++)
	{
	  os<<ops[j].first<<ops[j].second<<" ";
	}
	os<<std::endl;
      }	
      
      return os;
 } 

#endif
