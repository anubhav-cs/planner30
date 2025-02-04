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

#ifndef __BWD_APTK_STATE__
#define __BWD_APTK_STATE__

#include <bwd_strips_prob.hxx>
#include <bwd_types.hxx>
#include <bwd_fluent.hxx>
#include <iostream>

namespace aptk
{

namespace backward {

class Action;

class State
{
public:
	State( const STRIPS_Problem& p );


//    Fluent_Vec			m_fluent_vec;
//    Fluent_Set			m_fluent_set;
//    Fluent_Vec			m_goal_vec;
//    Fluent_Set			m_goal_set;
//    const STRIPS_Problem&		m_problem;
//    size_t				m_hash;
	State(State& p):m_problem(p.m_problem){
	    m_fluent_vec = p.m_fluent_vec;
	    m_fluent_set = p.m_fluent_set;
//	    m_goal_vec = p.m_goal_vec;
       // m_goal_set = p.m_goal_set;
//        m_hash = p.m_hash;

	}
	~State();

	Fluent_Vec& fluent_vec() 		{ return m_fluent_vec; }
	Fluent_Set& fluent_set() 		{ return m_fluent_set; }
	const Fluent_Vec& fluent_vec() const	{ return m_fluent_vec; }
	const Fluent_Set& fluent_set() const	{ return m_fluent_set; }

//	/** chao add
//	 *
//	 * @return
//	 */
//    Fluent_Vec& goal_vec() 		{ return m_goal_vec; }
//    Fluent_Set& goal_set() 		{ return m_goal_set; }
//    const Fluent_Vec& goal_vec() const	{ return m_goal_vec; }
//    const Fluent_Set& goal_set() const	{ return m_goal_set; }
	
	unsigned value_for_var( unsigned var ) const { return 0 == m_fluent_set.isset(var) ? 0 : 1; }

	void	set( unsigned f );
	void	unset( unsigned f );
	void	set( const Fluent_Vec& fv );
	void	unset( const Fluent_Vec& fv );
	void    reset();



	/** chao edit
	 *
	 * @param f
	 * @return
	 */

//    void	set_goal_set( unsigned f );
//    void	set_goal_set( const unsigned& f );
//    void	set_goal_unset(const unsigned& f );
//    void	set_goal_unset( unsigned f );
//    void	set_goal_set( const Fluent_Vec& fv );
//    void	set_goal_unset( const Fluent_Vec& fv );
//    void    set_goal_reset();
//
//
//    bool	set_goal_entails( const Fluent_Vec& fv ) const;
//
//
//    bool	set_goal_entails( unsigned f ) const { return goal_set().isset(f); }

	bool	entails( unsigned f ) const { return fluent_set().isset(f); }
	bool	entails( const State& s ) const;
	bool	entails( const Fluent_Vec& fv ) const;
	bool	entails( const Fluent_Vec& fv, unsigned& num_unsat ) const;
	size_t	hash() const;
	void	update_hash();

	State*	progress_through( const Action& a, Fluent_Vec* added = NULL, Fluent_Vec* deleted = NULL ) const;

	State*	progress_through_df( const Action& a ) const;

	State*	regress_through( const Action& a ) const;

	State*  regress_through_without_check( const Action& a ) const;

	void    progress_lazy_state_fwd(const Action* a, Fluent_Vec* added = NULL, Fluent_Vec* deleted = NULL);

	void    regress_lazy_state_fwd(const Action* a, Fluent_Vec* added = NULL, Fluent_Vec* deleted = NULL);

        void    progress_lazy_state_bwd(const Action* a, Fluent_Vec* added = NULL, Fluent_Vec* deleted = NULL);

        void    regress_lazy_state_bwd(const Action* a, Fluent_Vec* added = NULL, Fluent_Vec* deleted = NULL);

	const STRIPS_Problem&		problem() const;
  
        bool operator==(const State &a) const;

	void	print( std::ostream& os ) const;

protected:

	Fluent_Vec			m_fluent_vec;
	Fluent_Set			m_fluent_set;
    Fluent_Vec			m_goal_vec;
    Fluent_Set			m_goal_set;
	const STRIPS_Problem&		m_problem;
	size_t				m_hash;
};

inline	size_t State::hash() const {
	return m_hash;
}

inline bool State::operator==(const State &a) const {
  	return fluent_set() == a.fluent_set();
}

inline const STRIPS_Problem& State::problem() const
{
	return m_problem;
}

inline	void State::set( unsigned f ) 
{
	if ( entails(f) ) return;
	m_fluent_vec.push_back( f );
	m_fluent_set.set( f );
}



inline	void State::set( const Fluent_Vec& f )
{

	for ( unsigned i = 0; i < f.size(); i++ )
	{
		if ( !entails(f[i]) )
		{
			m_fluent_vec.push_back(f[i]);
			m_fluent_set.set(f[i]);
		}
	}
}

inline	void State::unset( unsigned f ) 
{
	if ( !entails(f) ) return;

	for ( unsigned k = 0; k < m_fluent_vec.size(); k ++ )
		if ( m_fluent_vec[k] == f )
		{
			for ( unsigned l = k+1; l < m_fluent_vec.size(); l++ )
				m_fluent_vec[l-1] = m_fluent_vec[l];
			m_fluent_vec.resize( m_fluent_vec.size()-1 );
			break;
		}

	m_fluent_set.unset( f );
}

inline	void State::unset( const Fluent_Vec& f )
{

	for ( unsigned i = 0; i < f.size(); i++ )
	{
		if ( !entails(f[i]) )
			continue;
		for ( unsigned k = 0; k < m_fluent_vec.size(); k ++ )
			if ( m_fluent_vec[k] == f[i] )
			{
				for ( unsigned l = k+1; l < m_fluent_vec.size(); l++ )
					m_fluent_vec[l-1] = m_fluent_vec[l];
				m_fluent_vec.resize( m_fluent_vec.size()-1 );
				break;
			}
		m_fluent_set.unset(f[i]);
	}
}

inline	void State::reset(  )
{
	m_fluent_vec.clear();
	m_fluent_set.reset();
}

inline bool	State::entails( const State& s ) const
{
	return entails( s.fluent_vec() );
}

inline std::ostream& operator<<(std::ostream &os, State &s);
inline std::ostream& operator<<(std::ostream &os, const State &s);


inline bool	State::entails( const Fluent_Vec& fv ) const
{
	for ( unsigned i = 0; i < fv.size(); i++ )
	  if ( !fluent_set().isset(fv[i]) ) {
	    return false;
	  }
	return true;
}

inline bool	State::entails( const Fluent_Vec& fv, unsigned& num_unsat ) const
{
	num_unsat = 0;
	for ( unsigned i = 0; i < fv.size(); i++ )
		if ( !fluent_set().isset(fv[i]) ) num_unsat++;
	return num_unsat == 0;
	
}
/** chao add
 *
 * @param os
 * @param s
 * @return
 */

//inline	void State::set_goal_set( unsigned f )
//{
//        if ( set_goal_entails(f) ) return;
//        m_goal_vec.push_back( f );
//        m_goal_set.set( f );
//}
//
//inline	void State::set_goal_set(const unsigned& f )
//    {
//        if ( set_goal_entails(f) ) return;
//        m_goal_vec.push_back( f );
//        m_goal_set.set( f );
//    }
//
//
//inline	void State::set_goal_set( const Fluent_Vec& f )
//{
//
//        for ( unsigned i = 0; i < f.size(); i++ )
//        {
//            if ( !set_goal_entails(f[i]) )
//            {
//                m_goal_vec.push_back(f[i]);
//                m_goal_set.set(f[i]);
//            }
//        }
//}
//
//
//
//inline	void State::set_goal_unset( unsigned f )
//{
//        if ( !set_goal_entails(f) ) return;
//
//        for ( unsigned k = 0; k < m_goal_vec.size(); k ++ )
//            if ( m_goal_vec[k] == f )
//            {
//                for ( unsigned l = k+1; l < m_goal_vec.size(); l++ )
//                    m_goal_vec[l-1] = m_goal_vec[l];
//                m_goal_vec.resize( m_goal_vec.size()-1 );
//                break;
//            }
//
//        m_goal_set.unset( f );
//    }
//inline  void State::set_goal_unset(const unsigned& f )
//{
//        if ( !set_goal_entails(f) ) return;
//
//        for ( unsigned k = 0; k < m_goal_vec.size(); k ++ )
//            if ( m_goal_vec[k] == f )
//            {
//                for ( unsigned l = k+1; l < m_goal_vec.size(); l++ )
//                    m_goal_vec[l-1] = m_goal_vec[l];
//                m_goal_vec.resize( m_goal_vec.size()-1 );
//                break;
//            }
//
//        m_goal_set.unset( f );
//    }
//
//
//
//inline void State:: set_goal_unset(const Fluent_Vec& f)
//
//{
//
//        for ( unsigned i = 0; i < f.size(); i++ )
//        {
//            if ( !entails(f[i]) )
//                continue;
//            for ( unsigned k = 0; k < m_goal_vec.size(); k ++ )
//                if ( m_goal_vec[k] == f[i] )
//                {
//                    for ( unsigned l = k+1; l < m_goal_vec.size(); l++ )
//                        m_goal_vec[l-1] = m_goal_vec[l];
//                    m_goal_vec.resize( m_goal_vec.size()-1 );
//                    break;
//                }
//            m_goal_set.unset(f[i]);
//        }
//}
//
//
//inline	void State::set_goal_reset(  )
//    {
//        m_goal_vec.clear();
//        m_goal_set.reset();
//    }
//
//inline bool	State::set_goal_entails( const Fluent_Vec& fv ) const
//{
//        for ( unsigned i = 0; i < fv.size(); i++ )
//            if ( !goal_set().isset(fv[i]) ) {
//                return false;
//            }
//        return true;
//    }


inline std::ostream& operator<<(std::ostream &os, State &s) {
  for(unsigned i = 0; i < s.fluent_vec().size(); i++) {
    os << s.problem().fluents()[s.fluent_vec()[i]]->signature();
    os << ", ";
  }
  os << std::endl;
  return os;
}


inline std::ostream& operator<<(std::ostream &os, const State &s) {
  for(unsigned i = 0; i < s.fluent_vec().size(); i++) {
    os << s.problem().fluents()[s.fluent_vec()[i]]->signature();
    os << ", ";
  }
  os << std::endl;
  return os;
}


}

}

#endif // State.hxx
