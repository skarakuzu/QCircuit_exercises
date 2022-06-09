
#ifndef CIRCUIT_HPP
#define CIRCUIT_HPP


#include<iostream>
#include<vector>
#include <algorithm>
#include <iterator>

class Circuit 
{

  public:
  
  Circuit(int nqubits) : nqubits_(nqubits) 
  {
 
    ops.resize(nqubits_);


    std::cout<<nqubits_<<" "<<ops.size()<<std::endl;

  }

  Circuit (const Circuit& other) = delete;

  void apply_rx(int iqubit, double degree)
  {
  ops[iqubit].push_back(std::make_pair("X",degree));
  }

  void apply_ry(int iqubit, double degree) 
  {
  ops[iqubit].push_back(std::make_pair("Y",degree));
  }

  void apply_rz(int iqubit, double degree)
  {
  ops[iqubit].push_back(std::make_pair("Z",degree));
  }


  void apply_cr(int iqubit_c, int iqubit_t, std::string basis_c, std::string basis_t, double degree_c, double degree_t)
  {
	auto itx = std::find_if( ops[iqubit_c].begin(), ops[iqubit_c].end(),
        [basis_c,degree_c](const std::pair<std::string, double>& element){ return element.first == basis_c && element.second == degree_c;} );

	if(itx!=ops[iqubit_c].end()) ops[iqubit_t].push_back(std::make_pair(basis_t,degree_t)); 
  
  }


  int num_qubits() const  {    return ops.size();  }


  std::vector<std::pair<std::string, double>> get_ops(int iqubit) const
  {
    return ops[iqubit];
  }


 friend std::ostream& operator<<(std::ostream& os, const Circuit& qc);

  ~Circuit(){} 
   
  private:

  int nqubits_;
  /* ops is the operators dynamically changing for each qubit and storing the basis info and the degree of rotation*/
  std::vector<std::vector<std::pair<std::string, double>>> ops;

};

 std::ostream& operator<<(std::ostream& os, const Circuit& qc)
 {
      for (int i=0; i<qc.num_qubits(); i++)
      {
	std::vector<std::pair<std::string, double>> ops = qc.get_ops(i);
   
	auto itx = std::find_if( ops.begin(), ops.end(),
        [](const std::pair<std::string, double>& element){ return element.first == "X";} );
        if(itx==ops.end()) ops.push_back(std::make_pair("X",0));

	auto ity = std::find_if( ops.begin(), ops.end(),
        [](const std::pair<std::string, double>& element){ return element.first == "Y";} );
        if(ity==ops.end()) ops.push_back(std::make_pair("Y",0));
	
	auto itz = std::find_if( ops.begin(), ops.end(),
        [](const std::pair<std::string, double>& element){ return element.first == "Z";} );
        if(itz==ops.end()) ops.push_back(std::make_pair("Z",0));
	
	for (int j=0; j<ops.size(); j++)
	{
	  os<<ops[j].first<<ops[j].second<<" ";
	}
	os<<std::endl;
      }	
      
      return os;
 } 

#endif
