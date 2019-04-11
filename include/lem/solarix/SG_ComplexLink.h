#if !defined SG_ComplexLink__H
 #define SG_ComplexLink__H

 #include <lem/ufstring.h>
 #include <lem/solarix/tree_link.h>
 #include <lem/solarix/SG_TagsList.h>

 namespace lem
 {
  namespace Iridium
  {
   class Macro_Parser;
  }
 }

 namespace Solarix
 {
  class SynGram;

 class SG_ComplexLink
 {
  public:
   int tl_id; // PK � ������� sg_tlink
   Tree_Link link; // ��� �����
   lem::UFString entry1; // ����� ������ 
   lem::UFString entry2; // � ����� ��������� ������� �������
   SG_TagsList tags;

  private:
   #if defined SOL_LOADTXT && defined SOL_COMPILER
   static void LoadPoint( lem::Iridium::Macro_Parser &txtfile, SynGram &gram, lem::UFString &entry );
   #endif

  public:
   SG_ComplexLink(void); 

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   void LoadTxt( lem::Iridium::Macro_Parser &txtfile, SynGram &gram );
   #endif
   
   // �������� ��������� ����������� ��� ���������� ������ ������
   bool operator<( const SG_ComplexLink &x ) const;

   inline bool operator==( const SG_ComplexLink &x ) const 
   { return entry1==x.entry1 &&
            link==x.link &&
            entry2==x.entry2 &&
            tags==x.tags; }

   inline Tree_Link GetLink(void) const { return link; }
   inline const lem::UFString& GetEntry1(void) const { return entry1; }
   inline const lem::UFString& GetEntry2(void) const { return entry2; }
   inline SG_TagsList GetTags(void) const { return tags; }
 };


 }
#endif
