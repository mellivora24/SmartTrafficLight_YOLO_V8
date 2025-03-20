import sys
import utils
from camera import Camera
from PyQt5.uic import loadUi
from PyQt5.QtGui import QPixmap
from PyQt5.QtWidgets import QMainWindow, QApplication

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.ui = loadUi(utils.resource_path('../assets/main.ui'), self)
        self.setWindowTitle("Smart Traffic Light System")

        self.cameras = []
        self.ui_elements = [
            (self.ui.hinh_1, self.update_frame_1),
            (self.ui.hinh_2, self.update_frame_2),
            (self.ui.hinh_3, self.update_frame_3),
            (self.ui.hinh_4, self.update_frame_4)
        ]

        for i, (hinh, update_func) in enumerate(self.ui_elements):
            try:
                camera = Camera(i)
                camera.frame_signal.connect(update_func)
                camera.start()
                self.cameras.append(camera)
            except Exception as e:
                print(f'Error: {str(e)}')

    def update_frame(self, frame, hinh):
        """Hàm chung để cập nhật khung hình."""
        if frame is not None:
            try:
                hinh.setPixmap(QPixmap.fromImage(frame))
            except Exception as e:
                print(f"Error: {str(e)}")

    # Các hàm update_frame sử dụng hàm chung
    def update_frame_1(self, frame):
        self.update_frame(frame, self.ui.hinh_1)

    def update_frame_2(self, frame):
        self.update_frame(frame, self.ui.hinh_2)

    def update_frame_3(self, frame):
        self.update_frame(frame, self.ui.hinh_3)

    def update_frame_4(self, frame):
        self.update_frame(frame, self.ui.hinh_4)

    def closeEvent(self, event):
        """Đóng tất cả camera khi thoát."""
        for camera in self.cameras:
            camera.stop()
        event.accept()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())