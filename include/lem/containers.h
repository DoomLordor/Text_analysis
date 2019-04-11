#ifndef LEM_CARRAY__H
#define LEM_CARRAY__H
#pragma once

// -----------------------------------------------------------------------------
// File CONTAINERS.H
//
// (c) Koziev Elijah
//
// Content:
// ����� BaseCollect - ������������� ������-��������� ��� ���������� ���������.
// ����� ��� �������� policy classes ��� �������, ������� ���������� �������
// ��������������� ��������� ��������� - ����� ��������� �������� (���� memcpy)
// ��� ��������� ����������� � �.�. ( operator=(...)).
//
// ��� ���� �� ������� ������������ �������, ������ (�� ���) ������ ����������
// �������� ��� ��� ����������. ��� ������� ������ - ����� ����������� ���������
// ������ �������� ���������.
//
// ����� �� ������������ ��������� ������ ������������ ������� - Collect ���
// �������� ��������� � �������������� �������������� �����������, MCollect
// ��� POD'��.
//
// 09.10.2005 - container are based on std::vector for better conformance
//              with STL
//
// 25.04.2007 - bug fix: an iterator of empty std::vector<T> can not be
//              dereferenced (MSVC 2005 only).
//
// 24.03.2008 - fill( T t ) method added
// -----------------------------------------------------------------------------
//
// CD->01.07.1995
// LC->17.04.2011
// --------------

 #include <lem/base_container.h>
 #include <lem/streams.h>

 // ����� ������� �� ������ ���������� ����� ������� ��� �����������.
 #undef max
 #undef min

 namespace lem
 {
  // ****************************************
  // Forward declaration.
  // ****************************************

  // Just to simplify the syntax of code in THIS file. The macro should be
  // undef'ed in the end of file.
  #undef BC
  #define BC   BaseCollect<T>

  #if defined LEM_GNUC
  #define SZT typename BC::size_type
  #else
  #define SZT BC::size_type
  #endif
  
  // ***************************************************************************
  // ����� Collect - ������������� ������-��������� ��� ���������� ���������.
  // ������� � �������������, ��� �������� �������� ����� �������������
  // ������������ �����������. ���� ��� ����������� ��������� ����������
  // ������������ memcpy, �� �������� ��������� ������ ����� ���������� � ������
  // LemMCollect, ��������������� � ����� [LEM_MARR.H].
  // ***************************************************************************
  template < class T >
  class Collect : public BaseCollect< T >
  {
   public:
   #if defined LEM_GNUC
    typedef typename BaseCollect<T>::size_type size_type;
    typedef typename BaseCollect<T>::iterator iterator;
    typedef typename BaseCollect<T>::const_iterator const_iterator;
   #else
    typedef BaseCollect<T>::size_type size_type;
   #endif

   #if defined LEM_GNUC
   inline typename lem::BaseCollect<T>::size_type size(void) const { return lem::BaseCollect<T>::size(); }
   inline bool empty(void) const { return lem::BaseCollect<T>::empty(); }
   inline void resize( typename BaseCollect<T>::size_type n ) { lem::BaseCollect<T>::resize(n); }
   inline void clear(void) { lem::BaseCollect<T>::clear(); }
   
   inline typename lem::BaseCollect<T>::const_iterator begin(void) const { return lem::BaseCollect<T>::begin(); }
   inline typename lem::BaseCollect<T>::const_iterator end(void) const { return lem::BaseCollect<T>::end(); }
   inline typename lem::BaseCollect<T>::iterator begin(void) { return lem::BaseCollect<T>::begin(); }
   inline typename lem::BaseCollect<T>::iterator end(void) { return lem::BaseCollect<T>::end(); }
   
   inline const T& operator[]( typename lem::BaseCollect<T>::size_type i ) const { return BaseCollect<T>::operator[](i); }
   inline       T& operator[]( typename lem::BaseCollect<T>::size_type i )       { return BaseCollect<T>::operator[](i); }
   #endif    
/*  
   #if defined __MINGW32__
    inline typename BaseCollect<T>::iterator       begin(void)       { return BaseCollect<T>::begin(); }
    inline typename BaseCollect<T>::const_iterator begin(void) const { return BaseCollect<T>::begin(); }

    inline typename BaseCollect<T>::iterator       end(void)       { return BaseCollect<T>::end(); }
    inline typename BaseCollect<T>::const_iterator end(void) const { return BaseCollect<T>::end(); }

    inline void resize( typename BaseCollect<T>::size_type n ) { BaseCollect<T>::resize(n); }
    inline void clear(void) { BaseCollect<T>::clear(); }
    inline bool empty(void) const { return BaseCollect<T>::empty(); }

    inline typename BaseCollect<T>::size_type size(void) { return BaseCollect<T>::size(); }

    inline const T& operator[]( typename lem::BaseCollect<T>::size_type i ) const { return lem::BaseCollect<T>::operator[](i); }
    inline       T& operator[]( typename lem::BaseCollect<T>::size_type i )       { return lem::BaseCollect<T>::operator[](i); }
   #endif
*/

   public:
    Collect( size_type n0=0 )
     : BaseCollect< T > (n0) {}

    Collect( const Collect<T> &x )
     : BaseCollect< T >(x) {}

    Collect( const T *Begin, const T *End )
     : BaseCollect< T >( Begin, End ) {}

    inline const Collect<T>& operator=( const Collect<T> &x )
    {
     return (const Collect<T>&)BaseCollect< T >
      :: operator=(x);
    }


   inline void SaveBin( lem::Stream &stream ) const
   {
    stream.write_int( CastSizeToInt(size()) );

    for( const_iterator i=begin(); i!=end(); i++ )
     i->SaveBin(stream);

    return;
   }


   inline void LoadBin( lem::Stream &stream )
   {
    size_type ni = stream.read_int();

    resize(ni);
    if( ni )
     for( iterator i=begin(); i!=end(); i++ )
      i->LoadBin(stream);

    return;
   }

   void fill( T t ) { std::fill( begin(), end(), t ); }

   int find( const T & t ) const
   {
    for( lem::Container::size_type i=0; i<size(); ++i )
     if( operator[](i)==t )
      return CastSizeToInt(i);

    return UNKNOWN;
   }
  };



  // ***********************************************************************
  // Basic container for POD-structs.
  // ����� MCollect - ������������� ������-��������� ��� ���������, �������
  // ����� ������������ ��� ������������� ������������, � ������� memcpy.
  // ***********************************************************************
  template < class T >
  class MCollect : public BaseCollect< T >
  {
   protected:
    #if defined __MINGW32__ || defined LEM_GNUC
    inline       T* get_Container(void)       { return (T*)&*begin(); }
    inline const T* get_Container(void) const { return (T*)&*begin(); }
    #endif

   public:
   #if defined LEM_GNUC      
    typedef typename BaseCollect< T >::size_type size_type;
   #else     
    typedef BaseCollect< T >::size_type size_type;
   #endif      

   #if defined LEM_GNUC
   inline size_type size(void) const { return lem::BaseCollect<T>::size(); }
   inline bool empty(void) const { return lem::BaseCollect<T>::empty(); }
   inline void resize( size_type n ) { lem::BaseCollect<T>::resize(n); }
   inline void clear(void) { lem::BaseCollect<T>::clear(); }
   
   inline typename lem::BaseCollect<T>::const_iterator begin(void) const { return lem::BaseCollect<T>::begin(); }
   inline typename lem::BaseCollect<T>::const_iterator end(void) const { return lem::BaseCollect<T>::end(); }
   inline typename lem::BaseCollect<T>::iterator begin(void) { return lem::BaseCollect<T>::begin(); }
   inline typename lem::BaseCollect<T>::iterator end(void) { return lem::BaseCollect<T>::end(); }
   
   inline const T& operator[]( size_type i ) const { return BaseCollect<T>::operator[](i); }
   inline       T& operator[]( size_type i )       { return BaseCollect<T>::operator[](i); }
   #endif    
/*
   #if defined __MINGW32__
    inline typename BaseCollect<T>::iterator       begin(void)       { return BaseCollect<T>::begin(); }
    inline typename BaseCollect<T>::const_iterator begin(void) const { return BaseCollect<T>::begin(); }

    inline typename BaseCollect<T>::iterator       end(void)       { return BaseCollect<T>::end(); }
    inline typename BaseCollect<T>::const_iterator end(void) const { return BaseCollect<T>::end(); }

    inline void resize( typename BaseCollect<T>::size_type n ) { BaseCollect<T>::resize(n); }
    inline void clear(void) { BaseCollect<T>::clear(); }
    inline bool empty(void) const { return BaseCollect<T>::empty(); }

    inline size_type size(void) { return BaseCollect<T>::size(); }

    inline const T& operator[]( size_type i ) const { return BaseCollect<T>::operator[](i); }
    inline       T& operator[]( size_type i )       { return BaseCollect<T>::operator[](i); }
   #endif
*/
   public:
    MCollect( size_type n0=0 )
     : BaseCollect< T >(n0) {}

    MCollect( const MCollect<T> &x )
     : BaseCollect< T >(x) {}

    MCollect( const T *Begin, const T *End )
     : BaseCollect< T >( Begin, End ) {}

    inline const MCollect<T>& operator=( const MCollect<T> &x )
    {
     return (const MCollect<T>&)BaseCollect< T >
      :: operator=(x);
    }


   inline void SaveBin( lem::Stream &stream ) const
   {
    size_type ni = size();
    stream.write( &ni, sizeof(ni) );
    if( !empty() )
     stream.write( get_Container(), size()*sizeof(T) );
    return;
   }


   inline void LoadBin( lem::Stream &stream )
   {
    size_type ni;
    stream.read(&ni,sizeof(ni));

    #if !defined LEM_BORLAND && !defined LEM_GNUC
    LEM_CHECKIT_Z(ni>=0);
    #endif

    resize(ni);
    if( ni )
     stream.read( get_Container(), size()*sizeof(T) );

    return;
   }

   // *******************************************************************
   // ������ �������� ���������� �������. ���� ����� ������ ������������
   // ������ ������������� ��������� �������.
   // *******************************************************************
   inline void Nullify(void) { std::fill( begin(), end(), static_cast<T>(0) ); }
   void fill( T t ) { std::fill( begin(), end(), t ); }

   // **********************************************************************
   // �������� ������ ��� �������� ������� ����� - ��������� ����� �� ����
   // ������.
   // **********************************************************************
   inline void SetBits( lem::uint8_t Bits )
   {
    ::memset( get_Container(), (int)Bits, (size_t)size() );
   }
  };


  // ************************************************************
  // ************************************************************
  template < class T >
  inline lem::Stream& operator << ( lem::Stream &stream, const BC &a )
  {
   a.SaveBin(stream);
   return stream;
  }


  // ************************************************************
  // ************************************************************
  template < class T >
  inline lem::Stream& operator >> ( lem::Stream &stream, const BC &a )
  {
   a.LoadBin(stream);
   return stream;
  }


  // ********************************************************************
  // ��������� ������� a � ��� ������, ���� ������� ��� �� ������������
  // � ������.
  // ********************************************************************
/*  template <class T >
  inline void add_once( BC &list, const T &x )
  {
   for( Container::size_type i=0; i<list.size(); i++ )
    if( list[i]==x )
     return;

   list.push_back(x);
   return;
  }*/

  // ****************************************************
  // Returns 'true' if any item of 'to_find' is in 'arr'
  // ****************************************************
  template <class T >
  inline bool find_any( const BC& arr, const BC& to_find )
  {
   for( Container::size_type i=0; i<to_find.size(); i++ )
    {
     const T& vi = to_find[i];

     for( Container::size_type j=0; j<arr.size(); j++ )
      if( arr[j]==vi )
       return true;
    }

   return false;
  }



  // ************************************************************
  // ************************************************************
  template < class T >
  inline void minmax( const BC& a, T& amin, T &amax )
  {
   if( a.empty() )
    return;

   amax=a.front(), amin=a.front();

   for( SZT i=1; i<a.size(); i++ )
    {
     amax = std::max( amax, a[i] );
     amin = std::min( amin, a[i] );
    }
  }



  // ************************************************************
  // ************************************************************
  template < class T >
  inline const T max( const BC& a )
  {
   T a_max=a.front();

   for( SZT i=1; i<a.size(); i++ )
    a_max < a[i] ? a_max=a[i] : a[i];

   return a_max;
  }



  // ************************************************************
  // ************************************************************
  template < class T >
  inline const T min( const BC& a )
  {
   T amin=a.front();

   for( SZT i=1; i<a.size(); i++ )
    amin > a[i] ? amin=a[i] : a[i];

   return amin;
  }



  // ************************************************************
  // ************************************************************
  template < class T >
  inline const T sum_up( const BC& a )
  {
   if( a.empty() )
    return T(0); // null value returned.

   T s=a.front();

   for( SZT i=1; i<a.size(); i++ )
    s += a[i];

   return s;
  }

  template < class T >
  inline bool operator==( const BC &a, const BC &b )
  {
   if( a.size()!=b.size() )
    return false;

   for( SZT i=0; i<a.size(); i++ )
    if( a[i]!=b[i] )
     return false;

   return true;
  }

  // ********************************
  // collection of int's.
  // ********************************
  typedef MCollect<int> IntCollect;

  // ��-�� ���������� ���� � ����������� ������� bool'�� ����������
  // ������ ��� ����� ������ int-��. �� ����������� ������ STL ��
  // ������� ���� GCC 4.x ������ �������� �� vector<bool>::operator[]=true
  typedef MCollect<int> BoolCollect;

 } //end of namespace 'lem'


 #undef BC 
 #undef SZT

#endif
