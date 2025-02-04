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

#ifndef __BWD_LANDMARK_GRAPH__
#define __BWD_LANDMARK_GRAPH__

#include <bwd_search_prob.hxx>
#include <bwd_heuristic.hxx>
#include <bwd_strips_state.hxx>
#include <bwd_strips_prob.hxx>
#include <action.hxx>
#include <vector>
#include <deque>
#include <iosfwd>

namespace aptk {

namespace backward {
namespace agnostic {
	

class Landmarks_Graph {
public:

	class Node {

	public:
		Node( unsigned p )
		: m_fluent( p ), m_consumed( false ), m_consumed_once( false ) {
		}
	
		~Node() {
		}
        /** chao edit
         *
         * @param n
         */
		void	add_del( Node* n ) {
			m_del.push_back( n );
		}
		void	add_edel( Node* n ) {
			m_edel.push_back( n );
		}
		void	add_precedent( Node* n ) {
			m_preceded_by.push_back( n );
		}

		void	add_precedent_gn( Node* n ) {
			m_preceded_by_gn.push_back( n );
		}

		void	add_requiring( Node* n ) {
			m_required_by.push_back( n );
		}

		void	add_requiring_gn( Node* n ) {
			m_required_by_gn.push_back( n );
		}

		unsigned	fluent() const { return m_fluent; }
		bool            is_consumed() const { return m_consumed; }
		bool            is_consumed_once() const { return m_consumed_once; }
		bool*           is_consumed_ptr() { return &m_consumed; }
		void            consume(){ m_consumed = true; m_consumed_once = true; }
		void            unconsume(){ m_consumed = false; }
		/** chao add
		 *
		 * @return
		 */
		bool            are_del_consumed() const{
			if(  m_del.empty() ) return true;
			for ( std::vector<Node* >::const_iterator it = m_del.begin(); it != m_del.end(); it++ )
				if( !(*it)->is_consumed() )
					return false;
			return true;
		}
		bool            are_edel_consumed() const{
			if(  m_edel.empty() ) return true;
			for ( std::vector<Node* >::const_iterator it = m_edel.begin(); it != m_edel.end(); it++ )
				if( !(*it)->is_consumed() )
					return false;
			return true;
		}
		bool            are_precedences_consumed() const{
			if(  m_preceded_by.empty() ) return true;
			for ( std::vector<Node* >::const_iterator it = m_preceded_by.begin(); it != m_preceded_by.end(); it++ )
				if( !(*it)->is_consumed() )
					return false;
			return true;
		}

		bool            are_gn_precedences_consumed() const{
			if(  m_preceded_by.empty() ) return true;
			for ( std::vector<Node* >::const_iterator it = m_preceded_by_gn.begin(); it != m_preceded_by_gn.end(); it++ )
				if( !(*it)->is_consumed() )
					return false;
			return true;
		}

		bool            are_requirements_consumed() const{
			if(  m_required_by.empty() ) return true;
			for ( std::vector<Node* >::const_iterator it = m_required_by.begin(); it != m_required_by.end(); it++ )
				if( !(*it)->is_consumed() )
					return false;
			return true;
		}

		bool            are_gn_requirements_consumed() const{
			if(  m_required_by_gn.empty() ) return true;
			for ( std::vector<Node* >::const_iterator it = m_required_by_gn.begin(); it != m_required_by_gn.end(); it++ )
				if( !(*it)->is_consumed_once() )
					return false;
			return true;
		}
		
		const std::vector<Node* >&
				preceded_by() const {
			return m_preceded_by;
		}

		/** chao add
		 *
		 * @param nq
		 * @return
		 */
		bool		is_del( Node* nq)  const {
			if(  m_del.empty() ) return false;
			for ( std::vector<Node* >::const_iterator it = m_del.begin(); it != m_del.end(); it++ )
				if( *it == nq )
					return true;
			return false;
		}
		bool		is_edel( Node* nq)  const {
			if(  m_edel.empty() ) return false;
			for ( std::vector<Node* >::const_iterator it = m_edel.begin(); it != m_edel.end(); it++ )
				if( *it == nq )
					return true;
			return false;
		}
		bool		is_preceded_by( Node* nq)  const {
			if(  m_preceded_by.empty() ) return false;
			for ( std::vector<Node* >::const_iterator it = m_preceded_by.begin(); it != m_preceded_by.end(); it++ )
				if( *it == nq )
					return true;
			return false;
		}
		bool		is_preceded_by_gn( Node* nq)  const {
			if(  m_preceded_by_gn.empty() ) return false;
			for ( std::vector<Node* >::const_iterator it = m_preceded_by_gn.begin(); it != m_preceded_by_gn.end(); it++ )
				if( *it == nq )
					return true;
			return false;
		}

		bool		is_required_by( Node* nq)  const {
			if(  m_required_by.empty() ) return false;
			for ( std::vector<Node* >::const_iterator it = m_required_by.begin(); it != m_required_by.end(); it++ )
				if( *it == nq )
					return true;
			return false;
		}
	
		bool		is_required_by_gn( Node* nq)  const {
			if(  m_required_by_gn.empty() ) return false;
			for ( std::vector<Node* >::const_iterator it = m_required_by_gn.begin(); it != m_required_by_gn.end(); it++ )
				if( *it == nq )
					return true;
			return false;
		}
		const std::vector<Node* >&
				preceded_by_gn() const {
			return m_preceded_by_gn;
		}
		/** chao add
		 *
		 * @return
		 */
		const std::vector<Node* >&
		get_del() const {
			return m_del;
		}
		const std::vector<Node* >&
		get_edel() const {
			return m_edel;
		}

		const std::vector<Node* >&
				required_by() const {
			return m_required_by;
		}

		const std::vector<Node* >&
				required_by_gn() const {
			return m_required_by_gn;
		}

	private:
		unsigned		m_fluent;
		bool                    m_consumed;
		bool                    m_consumed_once;
		std::vector<Node* >	m_preceded_by;
		std::vector<Node* >	m_preceded_by_gn;
		std::vector<Node* >	m_required_by;
		std::vector<Node* >	m_required_by_gn;
		std::vector<Node* > m_del;
		std::vector<Node* > m_edel;

	};

	Landmarks_Graph(const STRIPS_Problem& p);
	~Landmarks_Graph();

	bool				is_landmark( unsigned p ) const 	{ return m_fl_in_graph.isset(p); }
	const Node*			node( unsigned p ) const 		{ return m_fl_to_node[p]; }
	Node*   			node( unsigned p )      		{ return m_fl_to_node[p]; }
	const std::vector< Node* >&	nodes(  )          		        { return m_lm_graph; }
	void				preceding( unsigned p, Fluent_Vec& preceding ) const;
	void				greedy_preceding( unsigned p, Fluent_Vec& greedy_preceding ) const;
	void				following( unsigned p, Fluent_Vec& following ) const;
	/** chao add
	 *
	 * @param p
	 */
	Node*				generate_del( unsigned p ){        Node* n = new Node( p );
		return n;
	};
	Node*				generate_edel( unsigned p ){        Node* n = new Node( p );
		return n;
	};

	void				add_landmark( unsigned p );
    void                remove_landmark();
	void				add_landmark_for( unsigned p, unsigned q );

	void                            consume_node( unsigned p ){  m_fl_to_node[p]->consume(); }
	void                            unconsume_node( unsigned p ){  m_fl_to_node[p]->unconsume(); }

	void                            unconsume_all() {
		for ( std::vector< Node* >::const_iterator it = m_lm_graph.begin(); it != m_lm_graph.end(); it++ )
			(*it)->unconsume();
	}

	void                            get_leafs( Fluent_Vec& leafs ){

		for ( std::vector< Node* >::const_iterator it = m_lm_graph.begin(); it != m_lm_graph.end(); it++ ) {
			if( (*it)->is_consumed() ) continue;
			if(  (*it)->are_precedences_consumed() )
				leafs.push_back( (*it)->fluent() );				
		}
	}

    void  get_leafs_regression( Fluent_Vec& leafs ){

        for ( std::vector< Node* >::const_iterator it = m_lm_graph.begin(); it != m_lm_graph.end(); it++ ) {
            if( (*it)->is_consumed() ) continue;
            if(  (*it)->are_requirements_consumed() )
                leafs.push_back( (*it)->fluent() );
        }
    }


	

	unsigned			num_landmarks() const			{ return m_lm_graph.size(); }
	unsigned			num_landmarks_and_edges() const		
	{ 
		unsigned val=0;
		for ( std::vector< Node* >::const_iterator it = m_lm_graph.begin(); 
		      it != m_lm_graph.end(); it++ ) {
			Node* n = *it;			
			val++;
			

			if( !n->required_by_gn().empty() )
				for( std::vector< Node* >::const_iterator it_r = n->required_by_gn().begin(); it_r != n->required_by_gn().end(); it_r++ )
					val++;
					
			

			if( ! n->required_by().empty() )
				for( std::vector< Node* >::const_iterator it_r = n->required_by().begin(); it_r != n->required_by().end(); it_r++ )
						val++;						
				

		}	
		return val;
	}
	
	void				print( std::ostream& os ) const;

	void				print_dot( std::ostream& os ) const;

protected:
	
	const STRIPS_Problem&			m_strips_model;
	std::vector< Node* >			m_lm_graph;
	std::vector< Node* >			m_fl_to_node;
	Bit_Set					m_fl_in_graph;
};


}

}

}

#endif // bwd_landmark_graph.hxx
