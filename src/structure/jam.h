/* File: jam.h */
/* Tanggal: 28 Agustus 2016 */
/* Definisi ADT JAM */

#ifndef JAM_H
#define JAM_H

#include "boolean.h"

/* *** Definisi TYPE JAM <HH:MM> *** */
typedef struct {
	int HH; /* integer [0..23] */
	int MM; /* integer [0..59] */
} JAM;

/* *** Notasi Akses: selektor JAM *** */
#define Hour(J) (J).HH
#define Minute(J) (J).MM

/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */
boolean IsJAMValid (int H, int M);
/* Mengirim true  jika H,M dapat membentuk J yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah Jam */

/* *** Konstruktor: Membentuk sebuah JAM dari komponen-komponennya *** */
JAM MakeJAM (int HH, int MM);
/* Membentuk sebuah JAM dari komponen-komponennya yang valid */
/* Prekondisi : HH, MM valid untuk membentuk JAM */

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */
void BacaJAM (JAM * J);
/* I.S. : J tidak terdefinisi */
/* F.S. : J terdefinisi dan merupakan jam yang valid */
/* Proses : mengulangi membaca komponen HH, MM sehingga membentuk J */
/* yang valid. Tidak mungkin menghasilkan J yang tidak valid. */
/* Pembacaan dilakukan dengan mengetikkan komponen HH, MM.
   dalam satu baris, masing-masing dipisahkan 1 spasi, diakhiri enter. */
/* Jika JAM tidak valid maka diberikan pesan: "Jam tidak valid", dan pembacaan
   diulangi hingga didapatkan jam yang valid. */
/* Contoh:
   60 3
   Jam tidak valid
   1 3
   --> akan terbentuk JAM <1,3> */

void TulisJAM (JAM J);
/* I.S. : J sembarang */
/* F.S. :   Nilai J ditulis dg format HH hour (s) MM minute (s) jika minute tidak 0.*/

/* ***************************************************************** */
/* KELOMPOK KONVERSI TERHADAP TYPE                                   */
/* ***************************************************************** */
long JAMToMenit (JAM J);
/* Diberikan sebuah JAM, mengkonversi menjadi jumlah menit*/
/* Rumus : menit = 60*HH + MM */
/* Nilai maksimum = 60*23+59 */

JAM MenitToJAM (long N);
/* Mengirim  konversi detik ke JAM */
/* Catatan: Jika N >= 1440, maka harus dikonversi dulu menjadi jumlah menit yang
   mewakili jumlah menit yang mungkin dalam 1 hari, yaitu dengan rumus:
   N1 = N mod 1440, baru N1 dikonversi menjadi JAM */

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */

/* *** Operator aritmatika JAM *** */

JAM NextNMenit (JAM J, int N);
/* Mengirim N menit setelah J dalam bentuk JAM */


/* *** Kelompok Operator Aritmetika *** */
long Durasi (JAM JAw, JAM JAkh);
/* Mengirim JAkh-JAw dlm menit, dengan kalkulasi */
/* Jika JAw > JAkh, maka JAkh adalah 1 hari setelah JAw */

#endif
