#include <stdio.h>

int main() {
    int lua_chon;
    
    printf("=== HE THONG QUAN LY RAP PHIM CGV / LOTTE ===\n");
    printf("1. Dat ve xem phim & Xuat kho ve\n");
    printf("2. Quan ly ton kho Combo Bap Nuoc\n");
    printf("3. Tra cuu bang gia va chinh sach\n");
    printf("Lựa chọn của bạn (1-3): ");
    if (scanf("%d", &lua_chon) != 1) {
        printf("Loi: Du lieu nhap khong hop le!\n");
        return 1;
    }
    
    switch (lua_chon) {
        case 1: {
            int ma_phim_18, do_tuoi, loai_ghe, doi_tuong, ngay_chieu;
            float gia_ve_chuan;
            
            printf("--- CHUC NANG 1: DAT VE PHIM ---\n");
            printf("Phim co mac C18 khong? (1: Co, 0: Khong): ");
            scanf("%d", &ma_phim_18);
            printf("Nhap do tuoi khach hang: ");
            scanf("%d", &do_tuoi);
            printf("Nhap loai ghe (1: Thuong, 2: VIP, 3: Couple): ");
            scanf("%d", &loai_ghe);
            printf("Nhap doi tuong (1: HS/SV, 2: Khac): ");
            scanf("%d", &doi_tuong);
            printf("Nhap ngay chieu (1: Ngay thuong, 2: Cuoi tuan): ");
            scanf("%d", &ngay_chieu);
            printf("Nhap gia ve chuan (VND): ");
            scanf("%f", &gia_ve_chuan);
            
            if (do_tuoi <= 0 || gia_ve_chuan <= 0) {
                printf("LOI: Du lieu nhap vao khong hop le (Do tuoi hoac gia ve phai > 0)!\n");
                break;
            }
            
            if (ma_phim_18 == 1 && do_tuoi < 18) {
                printf("=== KET QUA XU LY VE ===\n");
                printf("TUYET DOI CAM: Khach hang chua du 18 tuoi de xem phim mac 18+! Xuat kho ve THAT BAI.\n");
                break;
            }
            
            float phu_thu_ghe = 0.0;
            if (loai_ghe == 2) {
                phu_thu_ghe = 15000.0;
            } else if (loai_ghe == 3) {
                phu_thu_ghe = 30000.0;
            }
            
            float phu_thu_cuoi_tuan = 0.0;
            if (ngay_chieu == 2) {
                phu_thu_cuoi_tuan = gia_ve_chuan * 0.10;
            }
            
            float giam_gia = 0.0;
            if (doi_tuong == 1 && ngay_chieu == 1) {
                giam_gia = gia_ve_chuan * 0.20;
            }
            
            float tong_tien = (gia_ve_chuan - giam_gia) + phu_thu_ghe + phu_thu_cuoi_tuan;
            
            printf("=== HOA DON XUAT VE CGV / LOTTE ===\n");
            printf("- Do tuoi khach hang: %d (Hop le)\n", do_tuoi);
            printf("- Gia ve chuan: %.1f VND\n", gia_ve_chuan);
            printf("- Phu thu ghe: %.1f VND\n", phu_thu_ghe);
            printf("- Phu thu cuoi tuan: %.1f VND\n", phu_thu_cuoi_tuan);
            printf("- Giam gia: %.1f VND\n", giam_gia);
            printf("-----------------------------------\n");
            printf("TONG TIEN THANH TOAN: %.1f VND\n", tong_tien);
            printf("XUAT KHO VE THANH CONG!\n");
            break;
        }
        case 2: {
            int ma_combo, so_luong_kho, so_luong_yeu_cau;
            
            printf("--- CHUC NANG 2: QUAN LY KHO BAP NUOC ---\n");
            printf("Nhap ma Combo (1: Single, 2: Couple, 3: Ultimate): ");
            scanf("%d", &ma_combo);
            printf("Nhap so luong ton kho hien tai: ");
            scanf("%d", &so_luong_kho);
            printf("Nhap so luong khach mua: ");
            scanf("%d", &so_luong_yeu_cau);
            
            if (so_luong_kho < 0 || so_luong_yeu_cau <= 0) {
                printf("LOI: So luong kho hoac so luong mua khong hop le!\n");
                break;
            }
            
            if (so_luong_yeu_cau > so_luong_kho) {
                printf("LOI: Tồn kho khong du cung ung! (Ton: %d, Yeu cau: %d)\n", so_luong_kho, so_luong_yeu_cau);
                break;
            }
            
            int so_luong_con_lai = so_luong_kho - so_luong_yeu_cau;
            float ty_le_con_lai = ((float)so_luong_con_lai / so_luong_kho) * 100.0;
            
            printf("=== BAO CAO XUAT KHO CONCESSION ===\n");
            printf("- Combo da chon: Combo (Ma %d)\n", ma_combo);
            printf("- So luong xuat kho: %d phan\n", so_luong_yeu_cau);
            printf("- So luong con lai trong kho: %d phan\n", so_luong_con_lai);
            printf("- Ty le ton kho con lai: %.2f%%\n", ty_le_con_lai);
            
            if (ty_le_con_lai < 10.0) {
                printf("- TRANG THAI KHO: MUC DONG NGUY HIEM - CAN NHAP KHO GAP\n");
            } else if (ty_le_con_lai <= 30.0) {
                printf("- TRANG THAI KHO: CANH BAO TONG KHO THAP\n");
            } else {
                printf("- TRANG THAI KHO: TON KHO AN TOAN\n");
            }
            break;
        }
        case 3:
            printf("--- TRA CUU BANG GIA VA CHINH SACH RAP ---\n");
            printf("1. Gia ve chuan: Tu 90,000 VND tuy theo rap.\n");
            printf("2. Phu thu ghe: VIP (+15,000 VND), Couple (+30,000 VND).\n");
            printf("3. Phu thu cuoi tuan: +10%% vao Thu 6, Thu 7, Chu Nhat.\n");
            printf("4. Giam gia HS/SV: Giam 20%% vao ngay thuong (Thu 2 den Thu 5).\n");
            break;
        default:
            printf("Loi: Luachon menu khong hop le! Vui long chay lai va chon tu 1 den 3.\n");
            break;
    }
    
    return 0;
}