// @(#)root/reflex:$Name:$:$Id:$
// Author: Stefan Roiser 2004

// Copyright CERN, CH-1211 Geneva 23, 2004-2005, All rights reserved.
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#ifndef ROOT_Reflex_UnionBuilder
#define ROOT_Reflex_UnionBuilder

// Include files
#include "Reflex/Builder/TypeBuilder.h"
#include "Reflex/Member.h"

namespace ROOT{
  namespace Reflex{

    // forward declarations
    class Union;
    class Type;
    
    /** 
     * @class UnionBuilderImpl UnionBuilder.h Reflex/Builder/UnionBuilder.h
     * @author Stefan Roiser
     * @date 14/3/2005
     * @ingroup RefBld
     */
    class UnionBuilderImpl {

    public:

      /** constructor */
      UnionBuilderImpl( const char * Name,
                        size_t size,
                        const std::type_info & ti );

      /** destructor */
      virtual ~UnionBuilderImpl() {}


      /**
       * AddItem will add one union item
       * @param Name the Name of the union item
       * @param TypeNth the TypeNth of the union item
       */
      void AddItem( const char * Name,
                    const Type & TypeNth );


      /** 
       * AddProperty will add a PropertyNth to the PropertyNth stack
       * which will be emtpied with the next build of a union 
       * or union item
       * @param  key the PropertyNth key
       * @param  value the value of the PropertyNth
       * @return a reference to the building class
       */
      void AddProperty( const char * key,
                        Any value );


      /** 
       * AddProperty will add a PropertyNth to the PropertyNth stack
       * which will be emtpied with the next build of a union 
       * or union item
       * @param  key the PropertyNth key
       * @param  value the value of the PropertyNth
       * @return a reference to the building class
       */
      void AddProperty( const char * key,
                        const char * value );

    private:

      /** the union currently being built */
      Union * fUnion;

      /** the last union item built */
      Member fLastMember;

    }; // class UnionBuilderImpl


    /** 
     * @class UnionBuilder UnionBuilder.h Reflex/Builder/UnionBuilder.h
     * @author Stefan Roiser
     * @date 30/3/2004
     * @ingroup RefBld
     */
    template < typename T >
    class UnionBuilder {

    public:    

      /** constructor */
      UnionBuilder();


      /** constructor */
      UnionBuilder(const char * Name );

      
      /** destructor */
      virtual ~UnionBuilder();

      
      /**
       * AddItem will add one union item
       * @param Name the Name of the union item
       * @param TypeNth the TypeNth of the union item
       * @return a reference to the UnionBuilder
       */
      template < typename U > 
        UnionBuilder & AddItem( const char * Name );
 

      /**
       * AddItem will add one union item
       * @param Name the Name of the union item
       * @param TypeNth the TypeNth of the union item
       * @return a reference to the UnionBuilder
       */
      UnionBuilder & AddItem( const char * Name,
                              const char * TypeNth );

      
      /** 
       * AddProperty will add a PropertyNth to the PropertyNth stack
       * which will be emtpied with the next build of a union 
       * or union item
       * @param  key the PropertyNth key
       * @param  value the value of the PropertyNth
       * @return a reference to the building class
       */
      template < typename P >
      UnionBuilder & AddProperty( const char * key, 
                                  P value );

    private:

      /** the union information */
      UnionBuilderImpl fUnionBuilderImpl;

    }; //class UnionBuilder
  } // namespace Reflex
} // namespace ROOT


//-------------------------------------------------------------------------------
template < typename T > 
inline ROOT::Reflex::UnionBuilder<T>::UnionBuilder() 
//-------------------------------------------------------------------------------
  : fUnionBuilderImpl( Tools::Demangle( typeid(T) ).c_str(),
                        sizeof(T),
                        typeid(T)) {}


//-------------------------------------------------------------------------------
template < typename T > 
inline ROOT::Reflex::UnionBuilder<T>::UnionBuilder( const char * Name )
//-------------------------------------------------------------------------------
  : fUnionBuilderImpl( Name,
                        sizeof(T),
                        typeid(T)) {}


//-------------------------------------------------------------------------------
template < typename T > template < typename U > 
inline ROOT::Reflex::UnionBuilder<T> &
ROOT::Reflex::UnionBuilder<T>::AddItem( const char * Name ) {
//-------------------------------------------------------------------------------
  fUnionBuilderImpl.AddItem( Name, TypeDistiller<U>::Get() );
  return * this;
}
                                 

//-------------------------------------------------------------------------------
template < typename T > 
inline ROOT::Reflex::UnionBuilder<T> &
ROOT::Reflex::UnionBuilder<T>::AddItem( const char * Name,
                                        const char * TypeNth ) {
//-------------------------------------------------------------------------------
  fUnionBuilderImpl.AddItem( Name, TypeBuilder(TypeNth));
  return * this;
}


//-------------------------------------------------------------------------------
template < typename T > template < typename P > 
inline ROOT::Reflex::UnionBuilder<T> & 
ROOT::Reflex::UnionBuilder<T>::AddProperty( const char * key, 
                                            P value ) {
//-------------------------------------------------------------------------------
  fUnionBuilderImpl.AddProperty( key, value );
  return * this;
}


#endif // ROOT_Reflex_UnionBuilder
