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

#ifndef __BWD_REACHABILITY__
#define __BWD_REACHABILITY__

#include <bwd_strips_prob.hxx>
#include <bwd_types.hxx>
#include <bit_set.hxx>
#include <vector>

namespace aptk {


namespace backward {
	
namespace agnostic {

	class	Reachability_Test {
	public:

		Reachability_Test( const STRIPS_Problem& p );
		~Reachability_Test();

		// Returns true if atom set g is reachable from state s 
		bool	is_reachable( const Fluent_Vec& s, const Fluent_Vec& g );
		// Returns true if atom set g is reachable from s, when removing action
		bool	is_reachable( const Fluent_Vec& s, const Fluent_Vec& g, unsigned action );
//		bool 	is_reachable( const Fluent_Vec& s, const Fluent_Vec& g, const Bit_Set& excluded );
        bool 	is_reachable(const Fluent_Vec& s, const Fluent_Vec& g, const Bit_Set& excluded );
		void	get_reachable_actions( const Fluent_Vec& s, const Fluent_Vec& g,  Bit_Set& reach_actions );
		/** chao add
		 *
		 */
        void	get_reachable_negation_actions( const Fluent_Vec& s, const Fluent_Vec& g,  Bit_Set& reach_actions );
        void	get_reachable_actions_original( const Fluent_Vec& s, const Fluent_Vec& g,  Bit_Set& reach_actions );
	protected:

		bool	apply_actions();
		/** chao add
		 *
		 * @return
		 */
        bool	apply_actions_original();
		void	initialize( const Fluent_Vec& s );
		/** chao add
		 *
		 */
        bool	check_negation( const Fluent_Vec& set );
        bool	apply_negation_actions();
        void	initialize_negation( const Fluent_Vec& s );
		bool	check( const Fluent_Vec& set );

		void	print_reachable_atoms();
	protected:

		const STRIPS_Problem&		m_problem;
		std::vector<bool>	m_reachable_atoms;
		std::vector<bool>	m_reach_next;
		/** chao add
		 *
		 */
        std::vector<bool>	m_reachable_negation_atoms;
        std::vector<bool>	m_reach_negation_next;
        Bit_Set			m_negation_action_mask;
		Bit_Set			m_action_mask;


	};

}

}

}

#endif // bwd_reachability.hxx
