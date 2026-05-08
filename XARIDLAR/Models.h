#pragma once

namespace XARIDLAR {

	using namespace System;

	public ref class Yetkazuvchi
	{
	public:
		property int Id;
		property String^ Ism;
		property String^ Telefon;
		property String^ Manzil;
	};

	public ref class Mahsulot
	{
	public:
		property int Id;
		property String^ Nom;
		property String^ Kategoriya;
		property double Narx;
		property int Miqdor;
	};

	public ref class Buyurtma
	{
	public:
		property int Id;
		property int YetkazuvchiId;
		property String^ YetkazuvchiNomi;
		property int MahsulotId;
		property String^ MahsulotNomi;
		property int Miqdor;
		property double Jami;
		property DateTime Sana;
		property String^ Holat;
	};
}
