#if !defined BACK_REF_CORREL__H
#define BACK_REF_CORREL__H
#pragma once

 #include <lem/quantors.h>
 #include <lem/solarix/ViolationHandler.h>


 namespace lem
 {
  class OFormatter;
 }

 namespace Solarix
 {
  class SynGram;

  struct BackRefCorrel
  {
   bool affirmative;
   int id_coord0; // ����������� ���������� �����, � ������������ ����

   lem::UCString name; // ��� ����������
   int id_coord1; // ���������� � ����������
   bool for_group; // �������� ��� ������ - ����������� � �������� ������� �������, ��� ��� ��� � ����� ������

   ViolationHandler violation_handler; // ����� �� ��������� ������������

   BackRefCorrel(void) : affirmative(true), id_coord0(UNKNOWN), id_coord1(-1), for_group(false) {}

   bool operator==( const BackRefCorrel &x ) const
   { return affirmative==x.affirmative &&
            name==x.name &&
            id_coord0==x.id_coord0 &&
            id_coord1==x.id_coord1 &&
            for_group==x.for_group &&
            violation_handler==x.violation_handler; }

   bool operator!=( const BackRefCorrel &x ) const
   { return affirmative!=x.affirmative ||
            name!=x.name ||
            id_coord0!=x.id_coord0 ||
            id_coord0!=x.id_coord0 ||
            for_group!=x.for_group ||
            violation_handler!=x.violation_handler; }

   void SaveTxt( lem::OFormatter &txt, SynGram &sg ) const;

   const ViolationHandler& GetViolationHandler() const { return violation_handler; }
  };

 }

#endif
