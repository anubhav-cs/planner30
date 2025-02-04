/*
Lightweight Automated Planning Toolkit
Copyright (C) 2012
Miquel Ramirez <miquel.ramirez@rmit.edu.au>
Nir Lipovetzky <nirlipo@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __NEGATION_FLUENT__
#define __NEGATION_FLUENT__

#include <bwd_types.hxx>
#include <strips_prob.hxx>

namespace aptk
{
namespace backward{

class Negation_Fluent
{
public:

	Negation_Fluent( STRIPS_Problem& p );
	~Negation_Fluent();

	unsigned	index() const;
	std::string	signature() const;
	std::vector<unsigned > constants() const ;
	Index_Vec&	pddl_objs_idx();
	Index_Vec&	pddl_types_idx();

	void		set_index( unsigned idx );
	void		set_signature( std::string signature );
	void		set_constants( std::vector<unsigned > constants );
	STRIPS_Problem& problem();

protected:

	STRIPS_Problem&			m_problem;
	unsigned			m_negation_index;
	std::string			m_signature;
	/** chao_edit
	 *
	 */
	 std::vector<unsigned > m_constants_vector;
};

inline unsigned		Negation_Fluent::index() const
{
	return m_negation_index;
}

inline	std::string	Negation_Fluent::signature() const
{
	return m_signature;
}

inline std::vector<unsigned > Negation_Fluent:: constants() const
{
	return  m_constants_vector;
}

inline void	Negation_Fluent::set_index( unsigned idx )
{
	m_negation_index = idx;
}

inline void	Negation_Fluent::set_signature( std::string sig )
{
	m_signature = sig;
}

inline void	Negation_Fluent::set_constants(std::vector<unsigned int> constants)
	{
		m_constants_vector = constants;
	}

}
}

#endif // bwd_fluent.hxx
