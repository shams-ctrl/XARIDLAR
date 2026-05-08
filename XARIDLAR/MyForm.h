#pragma once
#include "Models.h"

namespace XARIDLAR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class MyForm : public Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			if (!IsInDesignMode())
			{
				InitializeData();
				LoadSampleData();
				RefreshAllViews();
			}
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::ComponentModel::Container^ components;

		TabControl^ tabMain;
		TabPage^ tabYetkazuvchi;
		TabPage^ tabMahsulot;
		TabPage^ tabBuyurtma;
		TabPage^ tabHisobot;

		DataGridView^ dgvYetkazuvchi;
		TextBox^ txtYIsm;
		TextBox^ txtYTel;
		TextBox^ txtYManzil;
		Button^ btnYQosh;
		Button^ btnYTahrir;
		Button^ btnYOchir;

		DataGridView^ dgvMahsulot;
		TextBox^ txtMNom;
		TextBox^ txtMKategoriya;
		NumericUpDown^ numMNarx;
		NumericUpDown^ numMMiqdor;
		Button^ btnMQosh;
		Button^ btnMTahrir;
		Button^ btnMOchir;

		DataGridView^ dgvBuyurtma;
		ComboBox^ cmbYetkazuvchi;
		ComboBox^ cmbMahsulot;
		NumericUpDown^ numBMiqdor;
		DateTimePicker^ dtBuyurtmaSana;
		ComboBox^ cmbHolat;
		Button^ btnBQosh;
		Button^ btnBHolat;
		Button^ btnBOchir;

		Label^ lblJamiBuyurtma;
		Label^ lblTasdiqlangan;
		Label^ lblYetkazilgan;
		Label^ lblKutilmoqda;
		Label^ lblBekor;
		Button^ btnHisobotYangila;

		BindingList<Yetkazuvchi^>^ yetkazuvchilar;
		BindingList<Mahsulot^>^ mahsulotlar;
		BindingList<Buyurtma^>^ buyurtmalar;

		int yId;
		int mId;
		int bId;

		bool IsInDesignMode()
		{
			return (LicenseManager::UsageMode == LicenseUsageMode::Designtime);
		}

		void InitializeData()
		{
			yetkazuvchilar = gcnew BindingList<Yetkazuvchi^>();
			mahsulotlar = gcnew BindingList<Mahsulot^>();
			buyurtmalar = gcnew BindingList<Buyurtma^>();
			yId = 1;
			mId = 1;
			bId = 1;
		}

		void LoadSampleData()
		{
			yetkazuvchilar->Add(CreateSupplier(yId++, "Toshkent Savdo MChJ", "+998 71 123-45-67", "Toshkent, Chilonzor"));
			yetkazuvchilar->Add(CreateSupplier(yId++, "Samarqand Eksport", "+998 66 234-56-78", "Samarqand, Markaziy"));

			mahsulotlar->Add(CreateProduct(mId++, "Noutbuk Lenovo", "Elektronika", 8500000, 20));
			mahsulotlar->Add(CreateProduct(mId++, "Office Stul", "Mebel", 450000, 50));
			mahsulotlar->Add(CreateProduct(mId++, "Printer HP", "Elektronika", 1200000, 15));

			buyurtmalar->Add(CreateOrder(bId++, 1, "Toshkent Savdo MChJ", 1, "Noutbuk Lenovo", 3, 25500000, DateTime(2026, 3, 1), "Yetkazildi"));
			buyurtmalar->Add(CreateOrder(bId++, 2, "Samarqand Eksport", 2, "Office Stul", 10, 4500000, DateTime(2026, 3, 5), "Tasdiqlandi"));
		}

		Yetkazuvchi^ CreateSupplier(int id, String^ ism, String^ tel, String^ manzil)
		{
			Yetkazuvchi^ y = gcnew Yetkazuvchi();
			y->Id = id;
			y->Ism = ism;
			y->Telefon = tel;
			y->Manzil = manzil;
			return y;
		}

		Mahsulot^ CreateProduct(int id, String^ nom, String^ kategoriya, double narx, int miqdor)
		{
			Mahsulot^ m = gcnew Mahsulot();
			m->Id = id;
			m->Nom = nom;
			m->Kategoriya = kategoriya;
			m->Narx = narx;
			m->Miqdor = miqdor;
			return m;
		}

		Buyurtma^ CreateOrder(
			int id,
			int yetkazuvchiId,
			String^ yetkazuvchiNomi,
			int mahsulotId,
			String^ mahsulotNomi,
			int miqdor,
			double jami,
			DateTime sana,
			String^ holat)
		{
			Buyurtma^ b = gcnew Buyurtma();
			b->Id = id;
			b->YetkazuvchiId = yetkazuvchiId;
			b->YetkazuvchiNomi = yetkazuvchiNomi;
			b->MahsulotId = mahsulotId;
			b->MahsulotNomi = mahsulotNomi;
			b->Miqdor = miqdor;
			b->Jami = jami;
			b->Sana = sana;
			b->Holat = holat;
			return b;
		}

		void RefreshAllViews()
		{
			dgvYetkazuvchi->DataSource = nullptr;
			dgvYetkazuvchi->DataSource = yetkazuvchilar;
			dgvMahsulot->DataSource = nullptr;
			dgvMahsulot->DataSource = mahsulotlar;
			dgvBuyurtma->DataSource = nullptr;
			dgvBuyurtma->DataSource = buyurtmalar;
			FillCombos();
			RefreshHisobot();
		}

		void FillCombos()
		{
			cmbYetkazuvchi->Items->Clear();
			for each (Yetkazuvchi ^ y in yetkazuvchilar)
			{
				cmbYetkazuvchi->Items->Add(String::Format("{0} - {1}", y->Id, y->Ism));
			}

			cmbMahsulot->Items->Clear();
			for each (Mahsulot ^ m in mahsulotlar)
			{
				cmbMahsulot->Items->Add(String::Format("{0} - {1}", m->Id, m->Nom));
			}

			cmbHolat->Items->Clear();
			cmbHolat->Items->Add("Kutilmoqda");
			cmbHolat->Items->Add("Tasdiqlandi");
			cmbHolat->Items->Add("Yetkazildi");
			cmbHolat->Items->Add("Bekor qilindi");

			if (cmbHolat->Items->Count > 0) cmbHolat->SelectedIndex = 0;
			if (cmbYetkazuvchi->Items->Count > 0) cmbYetkazuvchi->SelectedIndex = 0;
			if (cmbMahsulot->Items->Count > 0) cmbMahsulot->SelectedIndex = 0;
		}

		int ParseIdFromCombo(String^ text)
		{
			array<String^>^ parts = text->Split('-');
			return Int32::Parse(parts[0]->Trim());
		}

		Yetkazuvchi^ FindSupplier(int id)
		{
			for each (Yetkazuvchi ^ y in yetkazuvchilar)
			{
				if (y->Id == id) return y;
			}
			return nullptr;
		}

		Mahsulot^ FindProduct(int id)
		{
			for each (Mahsulot ^ m in mahsulotlar)
			{
				if (m->Id == id) return m;
			}
			return nullptr;
		}

		void SyncOrderNames()
		{
			for each (Buyurtma ^ b in buyurtmalar)
			{
				Yetkazuvchi^ y = FindSupplier(b->YetkazuvchiId);
				Mahsulot^ m = FindProduct(b->MahsulotId);
				b->YetkazuvchiNomi = y != nullptr ? y->Ism : "Noma'lum";
				b->MahsulotNomi = m != nullptr ? m->Nom : "Noma'lum";
			}
		}

		void RefreshHisobot()
		{
			double jami = 0;
			double tasdiqlangan = 0;
			double yetkazilgan = 0;
			int kutilmoqda = 0;
			int bekor = 0;

			for each (Buyurtma ^ b in buyurtmalar)
			{
				jami += b->Jami;
				if (b->Holat == "Tasdiqlandi") tasdiqlangan += b->Jami;
				if (b->Holat == "Yetkazildi") yetkazilgan += b->Jami;
				if (b->Holat == "Kutilmoqda") kutilmoqda++;
				if (b->Holat == "Bekor qilindi") bekor++;
			}

			lblJamiBuyurtma->Text = String::Format("Jami buyurtma summasi: {0:N0} so'm", jami);
			lblTasdiqlangan->Text = String::Format("Tasdiqlangan: {0:N0} so'm", tasdiqlangan);
			lblYetkazilgan->Text = String::Format("Yetkazilgan: {0:N0} so'm", yetkazilgan);
			lblKutilmoqda->Text = String::Format("Kutilmoqda: {0}", kutilmoqda);
			lblBekor->Text = String::Format("Bekor qilingan: {0}", bekor);
		}

		Void BtnYQosh_Click(Object^ sender, EventArgs^ e)
		{
			if (String::IsNullOrWhiteSpace(txtYIsm->Text))
			{
				MessageBox::Show("Yetkazuvchi nomini kiriting.");
				return;
			}

			yetkazuvchilar->Add(CreateSupplier(yId++, txtYIsm->Text->Trim(), txtYTel->Text->Trim(), txtYManzil->Text->Trim()));
			txtYIsm->Clear();
			txtYTel->Clear();
			txtYManzil->Clear();
			SyncOrderNames();
			RefreshAllViews();
		}

		Void BtnYTahrir_Click(Object^ sender, EventArgs^ e)
		{
			if (dgvYetkazuvchi->CurrentRow == nullptr) return;
			Yetkazuvchi^ y = dynamic_cast<Yetkazuvchi^>(dgvYetkazuvchi->CurrentRow->DataBoundItem);
			if (y == nullptr) return;

			y->Ism = txtYIsm->Text->Trim();
			y->Telefon = txtYTel->Text->Trim();
			y->Manzil = txtYManzil->Text->Trim();
			SyncOrderNames();
			RefreshAllViews();
		}

		Void BtnYOchir_Click(Object^ sender, EventArgs^ e)
		{
			if (dgvYetkazuvchi->CurrentRow == nullptr) return;
			Yetkazuvchi^ y = dynamic_cast<Yetkazuvchi^>(dgvYetkazuvchi->CurrentRow->DataBoundItem);
			if (y == nullptr) return;

			for each (Buyurtma ^ b in buyurtmalar)
			{
				if (b->YetkazuvchiId == y->Id)
				{
					MessageBox::Show("Bu yetkazuvchi buyurtmalarda ishlatilgan.");
					return;
				}
			}

			yetkazuvchilar->Remove(y);
			RefreshAllViews();
		}

		Void DgvYetkazuvchi_SelectionChanged(Object^ sender, EventArgs^ e)
		{
			if (dgvYetkazuvchi->CurrentRow == nullptr) return;
			Yetkazuvchi^ y = dynamic_cast<Yetkazuvchi^>(dgvYetkazuvchi->CurrentRow->DataBoundItem);
			if (y == nullptr) return;
			txtYIsm->Text = y->Ism;
			txtYTel->Text = y->Telefon;
			txtYManzil->Text = y->Manzil;
		}

		Void BtnMQosh_Click(Object^ sender, EventArgs^ e)
		{
			if (String::IsNullOrWhiteSpace(txtMNom->Text))
			{
				MessageBox::Show("Mahsulot nomini kiriting.");
				return;
			}

			mahsulotlar->Add(CreateProduct(
				mId++,
				txtMNom->Text->Trim(),
				txtMKategoriya->Text->Trim(),
				(double)numMNarx->Value,
				(int)numMMiqdor->Value));

			txtMNom->Clear();
			txtMKategoriya->Clear();
			numMNarx->Value = 0;
			numMMiqdor->Value = 1;
			SyncOrderNames();
			RefreshAllViews();
		}

		Void BtnMTahrir_Click(Object^ sender, EventArgs^ e)
		{
			if (dgvMahsulot->CurrentRow == nullptr) return;
			Mahsulot^ m = dynamic_cast<Mahsulot^>(dgvMahsulot->CurrentRow->DataBoundItem);
			if (m == nullptr) return;

			m->Nom = txtMNom->Text->Trim();
			m->Kategoriya = txtMKategoriya->Text->Trim();
			m->Narx = (double)numMNarx->Value;
			m->Miqdor = (int)numMMiqdor->Value;
			SyncOrderNames();
			RefreshAllViews();
		}

		Void BtnMOchir_Click(Object^ sender, EventArgs^ e)
		{
			if (dgvMahsulot->CurrentRow == nullptr) return;
			Mahsulot^ m = dynamic_cast<Mahsulot^>(dgvMahsulot->CurrentRow->DataBoundItem);
			if (m == nullptr) return;

			for each (Buyurtma ^ b in buyurtmalar)
			{
				if (b->MahsulotId == m->Id)
				{
					MessageBox::Show("Bu mahsulot buyurtmalarda ishlatilgan.");
					return;
				}
			}

			mahsulotlar->Remove(m);
			RefreshAllViews();
		}

		Void DgvMahsulot_SelectionChanged(Object^ sender, EventArgs^ e)
		{
			if (dgvMahsulot->CurrentRow == nullptr) return;
			Mahsulot^ m = dynamic_cast<Mahsulot^>(dgvMahsulot->CurrentRow->DataBoundItem);
			if (m == nullptr) return;
			txtMNom->Text = m->Nom;
			txtMKategoriya->Text = m->Kategoriya;
			numMNarx->Value = Decimal(m->Narx);
			numMMiqdor->Value = m->Miqdor > 0 ? m->Miqdor : 1;
		}

		Void BtnBQosh_Click(Object^ sender, EventArgs^ e)
		{
			if (cmbYetkazuvchi->SelectedItem == nullptr || cmbMahsulot->SelectedItem == nullptr)
			{
				MessageBox::Show("Yetkazuvchi va mahsulot tanlang.");
				return;
			}

			int supplierId = ParseIdFromCombo(cmbYetkazuvchi->SelectedItem->ToString());
			int productId = ParseIdFromCombo(cmbMahsulot->SelectedItem->ToString());
			Yetkazuvchi^ y = FindSupplier(supplierId);
			Mahsulot^ m = FindProduct(productId);
			if (y == nullptr || m == nullptr) return;

			int qty = (int)numBMiqdor->Value;
			buyurtmalar->Add(CreateOrder(
				bId++,
				y->Id,
				y->Ism,
				m->Id,
				m->Nom,
				qty,
				m->Narx * qty,
				dtBuyurtmaSana->Value.Date,
				"Kutilmoqda"));

			RefreshAllViews();
		}

		Void BtnBHolat_Click(Object^ sender, EventArgs^ e)
		{
			if (dgvBuyurtma->CurrentRow == nullptr || cmbHolat->SelectedItem == nullptr) return;
			Buyurtma^ b = dynamic_cast<Buyurtma^>(dgvBuyurtma->CurrentRow->DataBoundItem);
			if (b == nullptr) return;
			b->Holat = cmbHolat->SelectedItem->ToString();
			RefreshAllViews();
		}

		Void BtnBOchir_Click(Object^ sender, EventArgs^ e)
		{
			if (dgvBuyurtma->CurrentRow == nullptr) return;
			Buyurtma^ b = dynamic_cast<Buyurtma^>(dgvBuyurtma->CurrentRow->DataBoundItem);
			if (b == nullptr) return;
			buyurtmalar->Remove(b);
			RefreshAllViews();
		}

		Void DgvBuyurtma_SelectionChanged(Object^ sender, EventArgs^ e)
		{
			if (dgvBuyurtma->CurrentRow == nullptr) return;
			Buyurtma^ b = dynamic_cast<Buyurtma^>(dgvBuyurtma->CurrentRow->DataBoundItem);
			if (b == nullptr) return;
			cmbHolat->SelectedItem = b->Holat;
		}

		Void BtnHisobotYangila_Click(Object^ sender, EventArgs^ e)
		{
			RefreshHisobot();
		}

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());

			this->tabMain = (gcnew TabControl());
			this->tabYetkazuvchi = (gcnew TabPage());
			this->tabMahsulot = (gcnew TabPage());
			this->tabBuyurtma = (gcnew TabPage());
			this->tabHisobot = (gcnew TabPage());

			this->dgvYetkazuvchi = (gcnew DataGridView());
			this->txtYIsm = (gcnew TextBox());
			this->txtYTel = (gcnew TextBox());
			this->txtYManzil = (gcnew TextBox());
			this->btnYQosh = (gcnew Button());
			this->btnYTahrir = (gcnew Button());
			this->btnYOchir = (gcnew Button());

			this->dgvMahsulot = (gcnew DataGridView());
			this->txtMNom = (gcnew TextBox());
			this->txtMKategoriya = (gcnew TextBox());
			this->numMNarx = (gcnew NumericUpDown());
			this->numMMiqdor = (gcnew NumericUpDown());
			this->btnMQosh = (gcnew Button());
			this->btnMTahrir = (gcnew Button());
			this->btnMOchir = (gcnew Button());

			this->dgvBuyurtma = (gcnew DataGridView());
			this->cmbYetkazuvchi = (gcnew ComboBox());
			this->cmbMahsulot = (gcnew ComboBox());
			this->numBMiqdor = (gcnew NumericUpDown());
			this->dtBuyurtmaSana = (gcnew DateTimePicker());
			this->cmbHolat = (gcnew ComboBox());
			this->btnBQosh = (gcnew Button());
			this->btnBHolat = (gcnew Button());
			this->btnBOchir = (gcnew Button());

			this->lblJamiBuyurtma = (gcnew Label());
			this->lblTasdiqlangan = (gcnew Label());
			this->lblYetkazilgan = (gcnew Label());
			this->lblKutilmoqda = (gcnew Label());
			this->lblBekor = (gcnew Label());
			this->btnHisobotYangila = (gcnew Button());

			this->SuspendLayout();
			this->tabMain->SuspendLayout();
			this->tabYetkazuvchi->SuspendLayout();
			this->tabMahsulot->SuspendLayout();
			this->tabBuyurtma->SuspendLayout();
			this->tabHisobot->SuspendLayout();

			this->Text = L"Kompaniya xaridlarini boshqarish";
			this->StartPosition = FormStartPosition::CenterScreen;
			this->ClientSize = System::Drawing::Size(1180, 720);
			this->BackColor = Color::FromArgb(240, 244, 252);
			this->Font = gcnew Drawing::Font(L"Segoe UI", 10);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;

			this->tabMain->Dock = DockStyle::Fill;
			this->tabMain->ItemSize = System::Drawing::Size(150, 38);
			this->tabMain->SizeMode = TabSizeMode::Fixed;
			this->tabMain->Appearance = TabAppearance::Normal;

			this->tabMain->Controls->Add(this->tabYetkazuvchi);
			this->tabMain->Controls->Add(this->tabMahsulot);
			this->tabMain->Controls->Add(this->tabBuyurtma);
			this->tabMain->Controls->Add(this->tabHisobot);

			this->tabYetkazuvchi->Text = L"Yetkazuvchilar";
			this->tabMahsulot->Text = L"Mahsulotlar";
			this->tabBuyurtma->Text = L"Buyurtmalar";
			this->tabHisobot->Text = L"Hisobot";

			this->tabYetkazuvchi->BackColor = Color::FromArgb(248, 250, 255);
			this->tabMahsulot->BackColor = Color::FromArgb(248, 250, 255);
			this->tabBuyurtma->BackColor = Color::FromArgb(248, 250, 255);
			this->tabHisobot->BackColor = Color::FromArgb(248, 250, 255);

			SetupGrid(this->dgvYetkazuvchi, Point(20, 20), System::Drawing::Size(760, 620));
			SetupGrid(this->dgvMahsulot, Point(20, 20), System::Drawing::Size(760, 620));
			SetupGrid(this->dgvBuyurtma, Point(20, 20), System::Drawing::Size(760, 620));

			this->dgvYetkazuvchi->SelectionChanged += gcnew EventHandler(this, &MyForm::DgvYetkazuvchi_SelectionChanged);
			this->dgvMahsulot->SelectionChanged += gcnew EventHandler(this, &MyForm::DgvMahsulot_SelectionChanged);
			this->dgvBuyurtma->SelectionChanged += gcnew EventHandler(this, &MyForm::DgvBuyurtma_SelectionChanged);

			AddLabel(this->tabYetkazuvchi, L"Ism", Point(820, 30));
			AddLabel(this->tabYetkazuvchi, L"Telefon", Point(820, 90));
			AddLabel(this->tabYetkazuvchi, L"Manzil", Point(820, 150));

			SetupTextBox(this->txtYIsm, Point(820, 55));
			SetupTextBox(this->txtYTel, Point(820, 115));
			SetupTextBox(this->txtYManzil, Point(820, 175));

			SetupButton(this->btnYQosh, L"Qo'shish", Point(820, 240), Color::FromArgb(25, 118, 210));
			SetupButton(this->btnYTahrir, L"Tahrirlash", Point(970, 240), Color::FromArgb(46, 125, 50));
			SetupButton(this->btnYOchir, L"O'chirish", Point(820, 290), Color::FromArgb(211, 47, 47));

			this->btnYQosh->Click += gcnew EventHandler(this, &MyForm::BtnYQosh_Click);
			this->btnYTahrir->Click += gcnew EventHandler(this, &MyForm::BtnYTahrir_Click);
			this->btnYOchir->Click += gcnew EventHandler(this, &MyForm::BtnYOchir_Click);

			AddLabel(this->tabMahsulot, L"Nom", Point(820, 30));
			AddLabel(this->tabMahsulot, L"Kategoriya", Point(820, 90));
			AddLabel(this->tabMahsulot, L"Narx", Point(820, 150));
			AddLabel(this->tabMahsulot, L"Miqdor", Point(820, 210));

			SetupTextBox(this->txtMNom, Point(820, 55));
			SetupTextBox(this->txtMKategoriya, Point(820, 115));

			this->numMNarx->Location = Point(820, 175);
			this->numMNarx->Size = System::Drawing::Size(330, 26);
			this->numMNarx->Maximum = Decimal(1000000000);
			this->numMNarx->ThousandsSeparator = true;

			this->numMMiqdor->Location = Point(820, 235);
			this->numMMiqdor->Size = System::Drawing::Size(330, 26);
			this->numMMiqdor->Minimum = Decimal(1);
			this->numMMiqdor->Maximum = Decimal(1000000);
			this->numMMiqdor->Value = Decimal(1);

			SetupButton(this->btnMQosh, L"Qo'shish", Point(820, 290), Color::FromArgb(25, 118, 210));
			SetupButton(this->btnMTahrir, L"Tahrirlash", Point(970, 290), Color::FromArgb(46, 125, 50));
			SetupButton(this->btnMOchir, L"O'chirish", Point(820, 340), Color::FromArgb(211, 47, 47));

			this->btnMQosh->Click += gcnew EventHandler(this, &MyForm::BtnMQosh_Click);
			this->btnMTahrir->Click += gcnew EventHandler(this, &MyForm::BtnMTahrir_Click);
			this->btnMOchir->Click += gcnew EventHandler(this, &MyForm::BtnMOchir_Click);

			AddLabel(this->tabBuyurtma, L"Yetkazuvchi", Point(820, 30));
			AddLabel(this->tabBuyurtma, L"Mahsulot", Point(820, 90));
			AddLabel(this->tabBuyurtma, L"Miqdor", Point(820, 150));
			AddLabel(this->tabBuyurtma, L"Sana", Point(820, 210));
			AddLabel(this->tabBuyurtma, L"Holat", Point(820, 270));

			this->cmbYetkazuvchi->DropDownStyle = ComboBoxStyle::DropDownList;
			this->cmbYetkazuvchi->Location = Point(820, 55);
			this->cmbYetkazuvchi->Size = System::Drawing::Size(330, 25);

			this->cmbMahsulot->DropDownStyle = ComboBoxStyle::DropDownList;
			this->cmbMahsulot->Location = Point(820, 115);
			this->cmbMahsulot->Size = System::Drawing::Size(330, 25);

			this->numBMiqdor->Location = Point(820, 175);
			this->numBMiqdor->Size = System::Drawing::Size(330, 26);
			this->numBMiqdor->Minimum = Decimal(1);
			this->numBMiqdor->Maximum = Decimal(100000);
			this->numBMiqdor->Value = Decimal(1);

			this->dtBuyurtmaSana->Location = Point(820, 235);
			this->dtBuyurtmaSana->Size = System::Drawing::Size(330, 26);
			this->dtBuyurtmaSana->Format = DateTimePickerFormat::Custom;
			this->dtBuyurtmaSana->CustomFormat = L"yyyy-MM-dd";

			this->cmbHolat->DropDownStyle = ComboBoxStyle::DropDownList;
			this->cmbHolat->Location = Point(820, 295);
			this->cmbHolat->Size = System::Drawing::Size(330, 25);

			SetupButton(this->btnBQosh, L"Yangi buyurtma", Point(820, 350), Color::FromArgb(25, 118, 210));
			SetupButton(this->btnBHolat, L"Holatni o'zgartirish", Point(820, 400), Color::FromArgb(46, 125, 50));
			SetupButton(this->btnBOchir, L"Buyurtmani o'chirish", Point(820, 450), Color::FromArgb(211, 47, 47));

			this->btnBQosh->Click += gcnew EventHandler(this, &MyForm::BtnBQosh_Click);
			this->btnBHolat->Click += gcnew EventHandler(this, &MyForm::BtnBHolat_Click);
			this->btnBOchir->Click += gcnew EventHandler(this, &MyForm::BtnBOchir_Click);

			this->lblJamiBuyurtma->Location = Point(60, 60);
			this->lblJamiBuyurtma->Size = System::Drawing::Size(850, 35);
			this->lblJamiBuyurtma->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 14);
			this->lblJamiBuyurtma->ForeColor = Color::FromArgb(21, 101, 192);

			this->lblTasdiqlangan->Location = Point(60, 120);
			this->lblTasdiqlangan->Size = System::Drawing::Size(850, 30);
			this->lblTasdiqlangan->Font = gcnew Drawing::Font(L"Segoe UI", 12);
			this->lblTasdiqlangan->ForeColor = Color::FromArgb(46, 125, 50);

			this->lblYetkazilgan->Location = Point(60, 170);
			this->lblYetkazilgan->Size = System::Drawing::Size(850, 30);
			this->lblYetkazilgan->Font = gcnew Drawing::Font(L"Segoe UI", 12);
			this->lblYetkazilgan->ForeColor = Color::FromArgb(2, 136, 209);

			this->lblKutilmoqda->Location = Point(60, 220);
			this->lblKutilmoqda->Size = System::Drawing::Size(850, 30);
			this->lblKutilmoqda->Font = gcnew Drawing::Font(L"Segoe UI", 12);
			this->lblKutilmoqda->ForeColor = Color::FromArgb(251, 140, 0);

			this->lblBekor->Location = Point(60, 270);
			this->lblBekor->Size = System::Drawing::Size(850, 30);
			this->lblBekor->Font = gcnew Drawing::Font(L"Segoe UI", 12);
			this->lblBekor->ForeColor = Color::FromArgb(211, 47, 47);

			SetupButton(this->btnHisobotYangila, L"Hisobotni yangilash", Point(60, 340), Color::FromArgb(25, 118, 210));
			this->btnHisobotYangila->Click += gcnew EventHandler(this, &MyForm::BtnHisobotYangila_Click);

			this->tabYetkazuvchi->Controls->Add(this->dgvYetkazuvchi);
			this->tabYetkazuvchi->Controls->Add(this->txtYIsm);
			this->tabYetkazuvchi->Controls->Add(this->txtYTel);
			this->tabYetkazuvchi->Controls->Add(this->txtYManzil);
			this->tabYetkazuvchi->Controls->Add(this->btnYQosh);
			this->tabYetkazuvchi->Controls->Add(this->btnYTahrir);
			this->tabYetkazuvchi->Controls->Add(this->btnYOchir);

			this->tabMahsulot->Controls->Add(this->dgvMahsulot);
			this->tabMahsulot->Controls->Add(this->txtMNom);
			this->tabMahsulot->Controls->Add(this->txtMKategoriya);
			this->tabMahsulot->Controls->Add(this->numMNarx);
			this->tabMahsulot->Controls->Add(this->numMMiqdor);
			this->tabMahsulot->Controls->Add(this->btnMQosh);
			this->tabMahsulot->Controls->Add(this->btnMTahrir);
			this->tabMahsulot->Controls->Add(this->btnMOchir);

			this->tabBuyurtma->Controls->Add(this->dgvBuyurtma);
			this->tabBuyurtma->Controls->Add(this->cmbYetkazuvchi);
			this->tabBuyurtma->Controls->Add(this->cmbMahsulot);
			this->tabBuyurtma->Controls->Add(this->numBMiqdor);
			this->tabBuyurtma->Controls->Add(this->dtBuyurtmaSana);
			this->tabBuyurtma->Controls->Add(this->cmbHolat);
			this->tabBuyurtma->Controls->Add(this->btnBQosh);
			this->tabBuyurtma->Controls->Add(this->btnBHolat);
			this->tabBuyurtma->Controls->Add(this->btnBOchir);

			this->tabHisobot->Controls->Add(this->lblJamiBuyurtma);
			this->tabHisobot->Controls->Add(this->lblTasdiqlangan);
			this->tabHisobot->Controls->Add(this->lblYetkazilgan);
			this->tabHisobot->Controls->Add(this->lblKutilmoqda);
			this->tabHisobot->Controls->Add(this->lblBekor);
			this->tabHisobot->Controls->Add(this->btnHisobotYangila);

			this->Controls->Add(this->tabMain);

			this->tabHisobot->ResumeLayout(false);
			this->tabBuyurtma->ResumeLayout(false);
			this->tabMahsulot->ResumeLayout(false);
			this->tabYetkazuvchi->ResumeLayout(false);
			this->tabMain->ResumeLayout(false);
			this->ResumeLayout(false);
		}
#pragma endregion

		void SetupGrid(DataGridView^ grid, Point location, System::Drawing::Size size)
		{
			grid->Location = location;
			grid->Size = size;
			grid->AutoGenerateColumns = true;
			grid->ReadOnly = true;
			grid->AllowUserToAddRows = false;
			grid->AllowUserToDeleteRows = false;
			grid->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
			grid->MultiSelect = false;
			grid->BackgroundColor = Color::White;
			grid->BorderStyle = BorderStyle::None;
			grid->CellBorderStyle = DataGridViewCellBorderStyle::SingleHorizontal;
			grid->EnableHeadersVisualStyles = false;
			grid->ColumnHeadersDefaultCellStyle->BackColor = Color::FromArgb(25, 118, 210);
			grid->ColumnHeadersDefaultCellStyle->ForeColor = Color::White;
			grid->ColumnHeadersDefaultCellStyle->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 10);
			grid->ColumnHeadersHeight = 36;
			grid->RowTemplate->Height = 32;
			grid->DefaultCellStyle->SelectionBackColor = Color::FromArgb(187, 222, 251);
			grid->DefaultCellStyle->SelectionForeColor = Color::Black;
			grid->AlternatingRowsDefaultCellStyle->BackColor = Color::FromArgb(245, 249, 255);
			grid->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
		}

		void SetupTextBox(TextBox^ textBox, Point location)
		{
			textBox->Location = location;
			textBox->Size = System::Drawing::Size(330, 26);
			textBox->BorderStyle = BorderStyle::FixedSingle;
		}

		void SetupButton(Button^ button, String^ text, Point location, Color color)
		{
			button->Text = text;
			button->Location = location;
			button->Size = System::Drawing::Size(145, 40);
			button->BackColor = color;
			button->ForeColor = Color::White;
			button->FlatStyle = FlatStyle::Flat;
			button->FlatAppearance->BorderSize = 0;
			button->Cursor = Cursors::Hand;
			button->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 10);
		}

		void AddLabel(Control^ parent, String^ text, Point location)
		{
			Label^ lbl = gcnew Label();
			lbl->Text = text;
			lbl->Location = location;
			lbl->Size = System::Drawing::Size(330, 22);
			lbl->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 10);
			lbl->ForeColor = Color::FromArgb(55, 71, 79);
			parent->Controls->Add(lbl);
		}
	};
}
