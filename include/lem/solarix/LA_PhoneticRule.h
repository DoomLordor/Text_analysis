#if !defined LA_PHONETIC_RULE__H
 #define LA_PHONETIC_RULE__H

 #include <lem/noncopyable.h>
 #include <lem/math/fp1.h>
 #include <lem/ucstring.h>
 #include <lem/solarix/lexem.h>

 namespace Solarix
 {

 /******************************************************************
  ����� ��������������/������������������ ������� ��� ������������
  ����-���������: ���������, �� ���� ������� ���������� �������.
 *******************************************************************/
 class GraphGram;
 class LA_PhoneticCondictor
 {
  public:
   typedef enum { PREFIX, AFFIX, UNLOCATED } LocType;

  private:
   LocType loc;
   lem::UCString context;

  public:
   LA_PhoneticCondictor(void);
   LA_PhoneticCondictor( const lem::UCString &str, bool IsPrefix, bool IsAffix );

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   LA_PhoneticCondictor( lem::Iridium::Macro_Parser &txtfile, GraphGram &gram );
   #endif

   #if defined SOL_CAA
   bool DoesMatch( const wchar_t *example ) const;
   bool Can_Subst( const lem::UCString &lex ) const;
   #endif

   inline int length(void) const { return context.length(); }

   inline wchar_t single(void) const
   {
    LEM_CHECKIT_Z( context.length()==1 );
    return context.front();
   }

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   void LoadTxt( lem::Iridium::Macro_Parser &txtfile, GraphGram &gram );
   bool operator==( const LA_PhoneticCondictor& x ) const;
   #endif

   inline bool IsPrefix(void) const { return loc==PREFIX; }
   inline bool IsAffix(void) const { return loc==AFFIX; }
   inline bool IsUnlocated(void) const { return loc==UNLOCATED; }

   inline const lem::UCString& GetContext(void) const { return context; }
 };

 /******************************************************************
  ����� ��������������/������������������ ������� ��� �����������
  ����-���������: �����, ��� ������������ ����� �������.
 *******************************************************************/
 class LA_PhoneticResult
 {
  private:
   Solarix::Lexem context;

  public:
   LA_PhoneticResult(void) {}
   LA_PhoneticResult( const lem::UCString &str );

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   LA_PhoneticResult( lem::Iridium::Macro_Parser &txtfile, Solarix::GraphGram &gram );
   #endif

   inline const Solarix::Lexem& GetContext(void) const { return context; }
   inline int length(void) const { return context.length(); }

   inline wchar_t single(void) const
   {
    LEM_CHECKIT_Z( context.length()==1 );
    return context.front();
   }

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   void LoadTxt( lem::Iridium::Macro_Parser &txtfile, Solarix::GraphGram &gram );
   bool operator==( const LA_PhoneticResult& x ) const;
   #endif
 };



 /****************************************************************
  ������� ��������� ��� ���������������� ������ �������������
  ����-���������, ����������� ������ ������������ ��������.

  ��� �������� ������ ��������� ���������� � ������� �����������
  �����������.
 *****************************************************************/
 class LA_PhoneticRule : lem::NonCopyable
 {
  private:
   int id;
   UCString name; // ��� ������� - ������������ ������ ��� ����������� ������������,
                  // ������ ������������, � ����������� ����������.
   int id_lang;   // ������� ����, ��� �������� ��������� �������

   lem::zbool is_prefix, is_affix;

   // ���� ������� - ���� ���������.
   LA_PhoneticCondictor head; // ��������� ������� - � ���������������� ��� �������� �������.
   LA_PhoneticResult    body; // ���� ������� - �� ����� ���� ��� ������������ �����.
   lem::Real1 val;                 // ������ ������������� ��������������

   int src_location;

  public:
   LA_PhoneticRule(void);
   LA_PhoneticRule( int Id, const lem::UCString &Name, int Id_Lang, bool IsPrefix,
    bool IsAffix, const lem::UCString &Condition, const lem::UCString &Result, lem::Real1 Rel, int SourceID );

   int GetId(void) const { return id; }
   void SetId( int _id ) { id=_id; }

   int GetSourceLocation(void) const { return src_location; }
   
   inline const lem::UCString&        GetName(void) const { return name; }
   inline const LA_PhoneticCondictor& GetCondition(void) const { return head; }
   inline const LA_PhoneticResult&    GetResult(void) const { return body; }
   inline lem::Real1                  GetVal(void)  const { return val;  }
   
   bool IsPrefix(void) const { return head.IsPrefix(); }
   bool IsAffix(void) const { return head.IsAffix(); }

   inline bool Is_1_to_1(void) const 
   { return head.length()==1 && body.length()==1; }

   // ������� ������� ����� � ������� �������.
   inline int GetnPoint(void) const { return head.length(); }

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   void LoadTxt( lem::Iridium::Macro_Parser &txtfile, GraphGram &gram );
   #endif

   #if defined SOL_CAA
   void Subst( const UCString &org, UCString &res ) const;
   #endif

   int GetHash(void) const;

   inline int GetLanguage(void) const { return id_lang; }
 };

 }

#endif
