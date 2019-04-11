// -----------------------------------------------------------------------------
// File YGRES.H
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Licensed under the terms of GNU Lesser GPL
//
// Content:
// ����� Compiler - ���������� ������� ���������.
//
// 19.11.2006 - ����������� ���� �������, ������ �������������
// 13.04.2007 - ������������ �������������� �������������� ���������� lem.
// 04.01.2010 - ��������� ��������� ���� �������������
// 29.08.2010 - ������� ��� ��������� ������ LITE
// 01.06.2011 - �������������� � ������ ������� ������ �������� � ��, � ��
//              � �������� �����
// -----------------------------------------------------------------------------
//
// CD->26.03.2004
// LC->02.07.2012
// --------------

#ifndef SOL_COMPILER__H
#define SOL_COMPILER__H
#pragma once

 #if defined SOL_LOADTXT

 #include <lem/solarix/solarix_binarization_options.h>
 #include <lem/console_application.h>
 #include <lem/solarix/sg_autom.h>
 #include <lem/solarix/SG_Affixtable.h>

 namespace Solarix
 {
  class Compiler //: public lem::Base_Application
  {
   public:
    lem::Ptr<Dictionary> sol_id;

   private:
    lem::Ptr<Solarix::Affix_Table> affix_table;
    const lem::CodeConverter* cp; // ������� �������� ��� ����������

    lem::PtrCollect<lem::UFString> xml_injection; // ���������� ������ � dictionary.xml

    void CompileAsciiProject( lem::Stream &proj_file );
    void CompileXmlProject( lem::Stream &proj_file );

   public:
    Compiler( lem::OFormatter &echo, lem::OFormatter &err, const Dictionary_Config &cfg );
    ~Compiler(void);

    string defines;    // ������ define'��
    int trace_level;   // ����������� ��������� �� ���� ����������
    UFString root_dir; // ������� � �������� �������������� �������

    Binarization_Options bin_options; // Options to control storing some parts in dictionary

    void CompileProject( lem::Stream &proj_file );
    void CompileFile( lem::Stream &sol_file );

    void Optimize(void);
    void PostCompile( const lem::Path &outdir );

    // ��������� � ���������������� ������� ��� ��������
    void CreateAffixTable(void);

    // ��������� ������ ������� ��� ��������
    void EmptyAffixTable(void);

    void SaveAlphabet( const lem::Path &db_path ) const;
    void SaveMorphology( lem::Stream &bin, const lem::Path &lexicon_db_path );
    void SaveSeeker( lem::Stream &bin ) const;
    void SaveAffixes( lem::Stream &bin ) const;
    void SaveThesaurusDb( const lem::Path &p ) const;
    void SavePrefixEntrySearcher( const lem::Path &p ) const;
    void SaveLemmatizer( const lem::Path &p, bool verbose ) const;
    void ParadigmasStorage( bool save );

    const Solarix::Dictionary& GetDictionary(void) const;

    void StemmerPrintInfo( lem::OFormatter &out ) const;
 
    inline void SetCodeConverter( const lem::CodeConverter *c ) { cp=c; }

    lem::UFString GetDictionaryXmlString(void) const;
  };

 } // end of namespace 'Solarix'

 #endif

#endif
