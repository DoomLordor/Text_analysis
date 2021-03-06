#if !defined Thesaurus__H
 #define Thesaurus__H

 #include <lem/smart_pointers.h>
 #include <lem/ptr_container.h>
 #include <lem/tuple.h>
 #include <lem/solarix/SG_ComplexLink.h>
 #include <lem/solarix/SG_NetLink.h>
 #include <lem/solarix/SG_LinkFlag.h>

 namespace Solarix
 {
  // ************************************************************* 
  // ��������, ��� ������������� ����. ������ ������ ������ �����
  // ���������� ���������� �������� ��� ������ �����������.
  // ************************************************************* 
  class SynGram;
  class TagSets;
  class ThesaurusTagDefs;
  class ThesaurusStorage;
  class WordLinkEnumerator;
  class PhraseLinkEnumerator;
  class PhraseNoteEnumerator;
  struct Dictionary_Config;
  class SG_TagFilter;
  class SQL_Production;
  struct ExactWordEntryLocator;

  class SG_Net
  {
   private:
    ThesaurusTagDefs *tag_defs; // ������ � ����������� ���������� �����

   public:
    SynGram *sg;
    ThesaurusStorage *db;
    bool do_delete_storage;
    TagSets *tag_sets; // ���������� ������� �����

    enum { DefaultSegmentationDelimiter=L' ' };

   private:
    lem::zint internal_offset_buffer;

    #if defined SOL_COMPILER && defined SOL_LOADTXT 
     // ������ ����������� ������ ��� ������������ ���������� - �����������
     // � �������������� ��� ���������� �������.

     typedef lem::foursome<
                           std::pair<UCString,UCString>, // �� �����:������
                           Tree_Link,                    // ������
                           std::pair<UCString,UCString>, // � �����:������
                           int                           // id ������ �����
                          > RawRecord;

     lem::Ptr<lem::BinaryFile> raw;
     int raw_count;

     std::map< std::pair< int /*entry key*/, Tree_Link >, std::pair<int/*entry key*/, int /*itags*/> > raw_links2;

     void Load_Complex(
                       Macro_Parser &txt,
                       const Binarization_Options &options
                      );

    #endif

   public:
    SG_Net( const Dictionary_Config &cfg );
    ~SG_Net(void);

    inline void StoreSG( SynGram *SG ) { sg=SG; }

    void SetStorage( ThesaurusStorage *_db, bool _do_delete );
    ThesaurusStorage& GetStorage(void) { return *db; }

    ThesaurusTagDefs& GetTagDefs(void) { return *tag_defs; }

    #if defined SOL_REPORT
    void Save_SQL( lem::OFormatter &out, const SQL_Production &sql_version, int min_entry_freq );
    #endif

    #if defined SOL_COMPILER
    std::pair<int/*ientry1*/,int/*itags*/> FindSingleLinked( int EntryKey0, const Tree_Link &Link ) const;

    void SaveThesaurusDb( const lem::Path &p );

    int LoadTags(
                 Macro_Parser &txt,
                 const Binarization_Options &options
                );

    void Load_Declaration(
                          Macro_Parser &txt,
                          const Binarization_Options &options
                         );

    void Compile(void);

    void LoadTxt(
                 Macro_Parser &txt,
                 const Binarization_Options &options
                );

    bool Load_Declaration(
                          Macro_Parser &txt,
                          const UCString &class0, 
                          const UCString &entry0, 
                          const Solarix::ExactWordEntryLocator & locator,
                          const Binarization_Options &options
                         );

    #endif

    SG_TagsList GetWordLinkTags( int id_link );
    SG_TagsList GetPhraseLinkTags( int id_link );
    SG_TagsList GetWordLinkTags( int id_tags, int id_link );
    SG_TagsList GetPhraseLinkTags( int id_tags, int id_link );

    // ����� ��������� ������

    #if defined SOL_CAA
    // ������������ ������ ������ ��������� (���������� ��������) ������
    void Find_Linked_Entries(
                             int EntryKey0, 
                             const Tree_Link& ilink,
                             lem::IntCollect &list,
                             const SG_TagFilter *filter=NULL
                            );

    lem::Ptr<SG_ComplexLink> GetComplexLink( int id_link );
    #endif
 
    WordLinkEnumerator* EnumerateWordLinks(void); 
    WordLinkEnumerator* EnumerateWordLinks( int ekey0 ); 
    WordLinkEnumerator* EnumerateWordLinks( int ekey0, int link_type ); 

    PhraseLinkEnumerator* EnumeratePhraseLinks(void); 
    PhraseLinkEnumerator* EnumeratePhraseLinks( int id_phrase1 ); 
    PhraseLinkEnumerator* EnumeratePhraseLinks( int id_phrase1, int link_type ); 
    PhraseLinkEnumerator* EnumeratePhraseLinks( int id_phrase1, const lem::MCollect<int> &link_types ); 

    // ������������� � ����������� ������ ���������� ��������
    // ����� ��������� ������ � �������� �������� depth.
    void Find_Linked_Entries(
                             int EntryKey0, 
                             float depth, 
                             std::set<int> &list,
                             bool incoming=true,
                             bool outgoing=true,
                             const lem::MCollect< Tree_Link > *allowed = NULL,
                             const SG_TagFilter *filter=NULL
                            );

    #if defined SOL_CAA
    // ���� ���� ���� ������ ilink ��� ������ EntryKey0?
    bool Is_Any_Linked(
                       int EntryKey0, 
                       const Tree_Link& ilink,
                       bool outgoing=true,
                       bool incoming=false,
                       const SG_TagFilter *filter=NULL
                      );

    int Find_Linked_Entry( int id_entry1, const Tree_Link& ilink, int id_entry2 );

    void Find_Linked_DbEntries(
                               const lem::UCString &word,
                               const lem::MCollect< Solarix::Tree_Link >& links,
                               lem::Collect<lem::UFString> &linked,
                               const SG_TagFilter *filter=NULL
                              );

    void Find_Linked_DbEntries(
                               const lem::UCString &word,
                               lem::Collect<lem::UFString> &linked,
                               const SG_TagFilter *filter=NULL
                              );

    void Find_Linked_DbEntries(
                               int tentry_id,
                               int link_type,
                               lem::MCollect<int> &linked_te_id,
                               const SG_TagFilter *filter=NULL
                              );

    void FindComplexLinks(
                          int tentry_id,
                          int link_type,
                          lem::MCollect<int> &tl_id,
                          lem::MCollect<int> &te_id,
                          const SG_TagFilter *filter=NULL
                         );

    #endif

    // ������� ������ ��������� ���� ���������������� � ���������
    int CountLinks( Tree_Link x ) const;
    int CountAllLinks(void) const;

    // Extract the list of all flags associated with a complex link
    void GetLinkFlags( int tl_id, lem::PtrCollect<SG_LinkFlag> & list ) const;
    void StoreLinkFlag( int tl_id, SG_LinkFlag &flag );
    void ClearLinkFlags( int tl_id );

    void SetLinkTags( int id_link, Solarix::SG_TagsList tags );
    void SetLinkTags( int id_link, int id_tags );
    void SetComplexLinkTags( int id_link, Solarix::SG_TagsList tags );
    void SetComplexLinkTags( int id_link, int id_tags );

    void BeginTx(void);
    void CommitTx(void);

    void RemoveComplexLink( int LinkID );
    void RemoveWordsLink( int LinkID );

    int AddWordsLink( int ekey0, int link_type, int ekey1, int id_tags );
    int AddWordsLink( int ekey0, int link_type, int ekey1, SG_TagsList tags );
    int AddComplexLink( int te_id0, int link_type, int te_id1, SG_TagsList tags );
    int AddComplexLink( int te_id0, int link_type, int te_id1, int id_tags );
    int AddWordLink( const SG_NetLink &lnk );

    int FindTag( const lem::UCString &tag_name ) const;
    std::pair<int,int> FindTagValue( const lem::UCString &tag_name, const lem::UCString &tag_value ) const;
    int FindTagValue( int TagID, const lem::UCString &tag_value ) const;

    lem::Ptr<SG_TagFilter> CompileTags( const lem::Collect< std::pair<lem::UCString,lem::UCString> > &tags ) const;

    int LoadTags( const lem::UFString &stags );
  };

 }

#endif
