# BÁO CÁO BÀI TẬP LẬP TRÌNH C: XÂY DỰNG MODULE QUẢN LÝ KHO VÉ VÀ TÍNH GIÁ VÉ RẠP PHIM CGV-LOTTE

> 👤 **Học viên:** Hoàng Công Dũng | **Mã SV:** PTIT-HCM-009
> 🏫 **Môn học:** it102-rl-hoangcongdung

---

## 📊 Sơ đồ thiết kế hệ thống (Activity Diagram)

> 💡 *Sơ đồ dưới đây được render tự động trực tiếp trên GitHub bằng Mermaid. Bạn cũng có thể tải file **`bt4.drawio`** trong repository này để mở và chỉnh sửa trực tiếp trên [Draw.io (diagrams.net)](https://app.diagrams.net).* 

```mermaid
graph TD
  Start([Bắt đầu chương trình]) --> Menu[Hiển thị Menu chính & Nhận lựa chọn]
  Menu --> Choice{Phân nhánh lựa chọn}
  Choice -- Lựa chọn 1 --> C1Start[Bắt đầu Chức năng 1: Đặt vé]
  C1Start --> InC1[Nhập: ma_phim_18, do_tuoi, loai_ghe, doi_tuong, ngay_chieu, gia_ve_chuan]
  InC1 --> ValC1{Kiểm chuẩn dữ liệu đầu vào > 0?}
  ValC1 -- Không hợp lệ --> ErrVal1[In lỗi nhập liệu & Dừng] --> End1([Kết thúc chức năng])
  ValC1 -- Hợp lệ --> Check18{ma_phim_18 == 1 VÀ do_tuoi < 18?}
  Check18 -- Đúng (Chưa đủ tuổi) --> Err18[In lỗi: Khách chưa đủ 18 tuổi] --> End1
  Check18 -- Sai (Đủ điều kiện) --> CalcVat[Tính phụ thu ghế, phụ thu cuối tuần & giảm giá]
  CalcVat --> CalcTotal[Tính tổng tiền thanh toán]
  CalcTotal --> PrintBill[In hóa đơn chi tiết & Thông báo xuất kho thành công] --> End1

  Choice -- Lựa chọn 2 --> C2Start[Bắt đầu Chức năng 2: Quản lý Kho]
  C2Start --> InC2[Nhập: ma_combo, so_luong_kho, so_luong_yeu_cau]
  InC2 --> ValC2{so_luong_kho >= 0 VÀ so_luong_yeu_cau > 0?}
  ValC2 -- Không hợp lệ --> ErrVal2[In lỗi nhập liệu kho & Dừng] --> End2([Kết thúc chức năng])
  ValC2 -- Hợp lệ --> CheckStock{so_luong_yeu_cau > so_luong_kho?}
  CheckStock -- Đúng (Thiếu hàng) --> ErrStock[In thông báo lỗi tồn kho không đủ] --> End2
  CheckStock -- Sai (Đủ hàng) --> CalcStock[Tính tồn kho còn lại & Tỷ lệ tồn kho]
  CalcStock --> EvalStock{Đánh giá tỷ lệ tồn kho}
  EvalStock -- < 10% --> StDanger[Trạng thái: Mức động nguy hiểm - Cần nhập kho gấp]
  EvalStock -- 10% đến 30% --> StWarn[Trạng thái: Cảnh báo tồn kho thấp]
  EvalStock -- > 30% --> StSafe[Trạng thái: Tồn kho an toàn]
  StDanger --> PrintReport[In báo cáo xuất kho concession] --> End2
  StWarn --> PrintReport
  StSafe --> PrintReport

  Choice -- Lựa chọn 3 --> C3Start[Chức năng 3: Tra cứu Bảng giá]
  C3Start --> PrintPrice[In bảng giá niêm yết & Chính sách ưu đãi] --> End3([Kết thúc chức năng])

  Choice -- Giá trị khác --> Default[In thông báo lỗi lựa chọn menu không hợp lệ] --> EndDef([Kết thúc chương trình])
```

---

## Nhiệm vụ 1: Phân tích yêu cầu và Thiết kế giải thuật

Bài thực hành yêu cầu xây dựng chương trình C mô phỏng hệ thống kiosk tự động tại các rạp chiếu phim CGV và Lotte, xử lý đồng thời hai nghiệp vụ cốt lõi: phân luồng đặt vé xem phim có kiểm soát độ tuổi, phụ thu, giảm giá và quản lý kho vật tư bắp nước concession.

Toàn bộ chương trình được thiết kế chạy tuần tự qua menu điều hướng 'switch-case' kết hợp cấu trúc rẽ nhánh 'if - else if - else' chuẩn ANSI C/C11, tuân thủ tuyệt đối quy tắc không sử dụng vòng lặp hay mảng.

- Kiểm tra nghiêm ngặt bẫy dữ liệu đầu vào: độ tuổi > 0, giá vé > 0, tồn kho >= 0 và số lượng mua > 0.
- Xử lý logic bẫy độ tuổi C18: Khán giả dưới 18 tuổi xem phim 18+ sẽ bị chặn ngay lập tức và hủy giao dịch xuất kho.
- Tính toán chính xác phụ thu ghế VIP/Couple, phụ thu cuối tuần 10% và chính sách giảm giá học sinh sinh viên 20% chỉ áp dụng vào ngày thường.

## Nhiệm vụ 2: Bảng đặc tả quy trình nghiệp vụ hệ thống

Dưới đây là bảng phân tích logic chi tiết các chức năng xử lý trong chương trình:

| Chức năng | Điều kiện nghiệp vụ | Công thức / Xử lý kỹ thuật | Trường hợp ngoại lệ (Edge Case) |
| --- | --- | --- | --- |
| Menu 1: Đặt vé | ma_phim_18 == 1 và do_tuoi < 18 | Báo lỗi và kết thúc ngay lập tức | TUYET DOI CAM: Khách hàng chưa đủ 18 tuổi |
| Menu 1: Đặt vé | Phụ thu ghế & cuối tuần | phu_thu_ghe + (gia_ve * 0.10) | Ghế thường 0đ, VIP 15k, Couple 30k |
| Menu 1: Đặt vé | Giảm giá học sinh sinh viên | giam_gia = gia_ve * 0.20 | Chỉ áp dụng khi ngay_chieu == 1 (Ngày thường) |
| Menu 2: Kho bắp | so_luong_yeu_cau > so_luong_kho | In cảnh báo thiếu hàng và dừng | LOI: Tồn kho không đủ cung ứng |
| Menu 2: Kho bắp | Đánh giá tỷ lệ tồn kho | ty_le = (con_lai / kho_ban_dau) * 100 | Nguy hiểm (<10%), Cảnh báo (10-30%), An toàn (>30%) |
| Menu 3 & Khác | Lựa chọn menu không hợp lệ | In thông báo mặc định | Loi: Lua chon menu khong hop le! |

## Nhiệm vụ 3: Đóng góp Mã nguồn hoàn chỉnh (main.c)

Mã nguồn được viết sạch sẽ, sử dụng tên biến tiếng Việt không dấu rõ nghĩa, biên dịch hoàn toàn sạch lỗi cảnh báo với 'gcc -Wall main.c -o main'.

---

## 📁 Danh sách tệp tin nộp bài trong Repository
- 📝 `bt4.docx`: Báo cáo tài liệu phân tích nghiệp vụ hoàn chỉnh.
- 🎨 `bt4.drawio`: File thiết kế sơ đồ chuẩn theo quy định đề bài (mở trực tiếp bằng [Draw.io](https://app.diagrams.net) hoặc Lucidchart).
- 💻 `main.c`: Mã nguồn chương trình.
