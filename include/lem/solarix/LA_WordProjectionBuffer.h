#ifndef LA_WordProjectionBuffer__H
#define LA_WordProjectionBuffer__H
#pragma once

 #include <lem/queue.h>
 #include <lem/process.h>
 #include <lem/RWULock.h>
 #include <lem/ptr_container.h>
 #include <lem/math/fp1.h>
 #include <lem/solarix/LA_ProjectInfo.h>
 #include <lem/solarix/lexem.h>
 #include <lem/solarix/WordCoord.h>
 #include <lem/solarix/ProjScore.h>

 namespace Solarix
 {
  class LA_RecognitionTrace;

  class LA_WordProjection
  {
   private:
    RC_Lexem A;
    lem::MCollect<Word_Coord> WC;
    lem::MCollect<ProjScore> val;
    long used_n_time; // ������� ��� �������� �������������� ����������

    inline void Init( const LA_WordProjection &wp )
    {
     used_n_time = wp.used_n_time;
     A           = wp.A;
     WC          = wp.WC;
     val         = wp.val;
     return;
    }


   public:
    LA_WordProjection(void);
    LA_WordProjection( const LA_WordProjection &x );
    LA_WordProjection(
                      const RC_Lexem &a,
                      const lem::MCollect<Word_Coord> &wc,
                      const lem::MCollect<ProjScore> &v,
                      long Used_n_Time
                     );


    #if defined SOL_LOADBIN
    LA_WordProjection( lem::Stream &bin );
    #endif

    const LA_WordProjection& operator=( const LA_WordProjection &wp );

    void Add( const LA_WordProjection &src );

    inline void Used(void) { used_n_time++; }

    inline const RC_Lexem& GetContent(void) const { return A; }

    inline long                        GetnUsed(void) const { return used_n_time; }
    inline const lem::MCollect<Word_Coord>& GetCoord(void) const { return WC;  }
    inline const lem::MCollect<ProjScore>& GetVal(void)   const { return val; }

    inline bool operator==( const LA_WordProjection &x ) const
    { return A==x.A && WC==x.WC; }

    inline bool operator<( const LA_WordProjection &WP ) const
    { return used_n_time < WP.used_n_time; }

    #if defined SOL_LOADBIN
    void LoadBin( lem::Stream &bin );
    #endif

    #if defined SOL_SAVEBIN
    void SaveBin( lem::Stream &bin ) const;
    #endif

    #if defined SOL_REPORT
    void Print( OFormatter &dst_stream, const LexicalAutomat &la ) const;
    void PrintInfo( OFormatter &dst_stream, SynGram &gram ) const;
    #endif
  };

  /********************************************************************
   ������ �������������� �������� ������������ �� ��������, ������ ���
   ������������� ���������� � ����� � ��� �� ����� (���� Char). �����
   ������������ ��� ������� ���� �������������� �������� ���
   ������������ ��������.
  *********************************************************************/
  struct LA_ProjList : public lem::Collect<LA_WordProjection>
  {
   wchar_t Char;

   LA_ProjList(void);
   LA_ProjList( wchar_t ch );
   LA_ProjList( const LA_ProjList &l );

   void operator=( const LA_ProjList &l );

   inline const LA_WordProjection& get( int i ) const { return operator[](i); }

   #if defined SOL_LOADBIN
   void LoadBin( lem::Stream &bin );
   #endif

   #if defined SOL_SAVEBIN
   void SaveBin( lem::Stream &bin ) const;
   #endif 

   void ReSort(void);

   #if defined SOL_REPORT
   void PrintInfo( OFormatter &dst_stream, SynGram &gram ) const;
   #endif
  };



  /*********************************************************************
  ��� �������������� �������� ������������. ��������� ������ �� ��������
  ������� �� ������������� �������� ��������������� ������������.
  **********************************************************************/
  const int SOL_LA_MAX_PRECACHE = 32; // ������������ ������ ���������� ������
                                      // � ���� ��������.

  class LexicalAutomat;
  class LA_WordProjBuffer
  {
   private:
    lem::Queue<LA_WordProjection> buffer; // ��������������� �����.
    lem::Collect<LA_ProjList> list;       // ��������� ��� ����������� � ����
                                     // ������� ���������.

    bool use_compiled; // ������������ �� ���������������� �������� ������
    bool update_list; // ��������� �� ���.

    #if defined LEM_THREADS && defined SOL_CAA
    lem::Process::RWU_Lock cs;
    #endif

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    bool optimized;
    #endif

    int nmaxproj; // ������������ ����� ��������� � ����.
    long n_calls; // ����� ��������� � ���� ��� ��������.
    long n_succ;  // ����� �������� �������� ��� ����� ����.
    int NTOT;     // ����� ����� �������� ��������� �� ���� ����������
                  // ���������� ������.
    int n_succ_prim; // ����� �������� �������� ����� ��������� �����.

    int LocateSublist( const RC_Lexem &to_be_found ) const;

    int GetN(void) const;

    #if defined SOL_CAA
    void Pick_Projection(
                         LA_ProjList *sublist,
                         int i_proj,
                         lem::MCollect<Word_Coord> &coord_list,
                         lem::MCollect<ProjScore> &val_list,
                         lem::PtrCollect<LA_ProjectInfo>& prj_extra_inf
                        );


    bool Find_In_Live_Cache(
                            const RC_Lexem &to_be_found,
                            lem::MCollect<Word_Coord> &coord_list,
                            lem::MCollect<ProjScore> &val_list,
                            lem::PtrCollect<LA_ProjectInfo>& prj_extra_inf
                           );
    #endif                           


   public:
    LA_WordProjBuffer(void);

    void SetMaxSize( int n );

    #if defined SOL_LOADTXT && defined SOL_COMPILER
    void Adjust( const GraphGram &gram );
    void Compile( const lem::Path &outdir );
    void Optimize(void);
    #endif

    void Resort(void);
    void Add( const LA_WordProjection &WP );

    #if defined SOL_CAA
    bool Project(
                 const RC_Lexem &to_be_found,
                 lem::MCollect<Word_Coord> &coord_list,
                 lem::MCollect<ProjScore> &val_list,
                 lem::PtrCollect<LA_ProjectInfo> &prj_extra_inf,
                 int id_lang,
                 LA_RecognitionTrace *trace
                );
    #endif

    #if defined SOL_LOADBIN
    void LoadBin( lem::Stream &bin );
    #endif

    #if defined SOL_SAVEBIN
    void SaveBin( lem::Stream &bin ) const;
    #endif

    #if defined SOL_REPORT
    void Report( OFormatter &dst_stream, const LexicalAutomat &la ) const;
    void PrintMap( OFormatter &dst_stream, SynGram &gram) const;
    #endif

    inline bool Is_Full(void) const
    { return int(buffer.size())>=SOL_LA_MAX_PRECACHE; }
  };

 } // namespace 'Solarix'

#endif
