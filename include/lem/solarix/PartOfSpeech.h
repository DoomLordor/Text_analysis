#if !defined PartOfSpeech__H
 #define PartOfSpeech__H

 #include <lem/ptr_container.h>
 #include <lem/solarix/gram_class.h>


 namespace Solarix
 {
  struct ImportFiltrerCoords : lem::NonCopyable
  {
   lem::MCollect<Solarix::GramCoordAdr> coords;
   int aux_type;
   lem::UCString aux_type_str;

   ImportFiltrerCoords() : aux_type(UNKNOWN) {}

   bool empty() const { return coords.empty() && aux_type==UNKNOWN; }
  };

  class Grammar;
  class SG_Class : public GramClass
  {
   public:
    int id_lang; // Language id for the word entries belonging for this class.
    int value; // �������� ������, 0 - �����, 1 - ��������� �������, 10 - �������������� �����
    bool closed_class; // ��������� ������ �� ��������� � ��������� ������ ������������� �� ���������

   protected:
    #if defined SOL_LOADTXT && defined SOL_COMPILER
    virtual bool Load_Private_Data( 
                                   const lem::Iridium::BethToken &t,
                                   lem::Iridium::Macro_Parser &txtfile,
                                   Solarix::Grammar& gram
                                  );
    void LoadImport( lem::Iridium::Macro_Parser &txtfile, Solarix::Grammar& gram );
    #endif

    #if defined SOL_SAVETXT
    virtual void Save_Private_Txt( lem::OFormatter& txtfile, const Solarix::Grammar& gram ) const;
    #endif

    #if defined SOL_LOADBIN 
    virtual void LoadBin( lem::Stream &bin );
    #endif

    #if defined SOL_SAVEBIN
    virtual void SaveBin( lem::Stream &bin ) const;
    #endif

   public:
    #if defined SOL_LOADTXT && defined SOL_COMPILER
    // ������ ������� ��������� - ������������ ������ �� ������ ����������
    lem::MCollect<Solarix::GramCoordAdr> import_coord; // ����� ���������� �������������
    lem::MCollect<int> import_class; // �� ������ ��������������� ������ ������ �� ��������� �������������
    lem::Ptr_NC_Collect<ImportFiltrerCoords> import_filters; // ��� ����������� ������ - �� ����� ����������� ���� �����
    #endif

   public:
    SG_Class(void);

    int GetLanguage() const { return id_lang; }
    int GetValue() const { return value; }
    bool IsClosed() const { return closed_class; }

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    inline bool HasImport() const { return !import_coord.empty(); }
    bool IsImportableAttribute( const GramCoordAdr &coord ) const;
    #endif
  };  

 }
#endif
