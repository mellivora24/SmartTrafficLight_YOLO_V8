import cv2
from PyQt5.QtGui import QImage
from PyQt5.QtCore import QThread, pyqtSignal

class Camera(QThread):
    frame_signal = pyqtSignal(object)

    def __init__(self, camera_index):
        super().__init__()
        self.running = True
        self.camera = cv2.VideoCapture(camera_index)

    def run(self):
        while self.running:
            ret, frame = self.camera.read()
            if ret:
                rgb_image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
                h, w, ch = rgb_image.shape
                bytes_per_line = ch * w
                convert_to_qt_format = QImage(rgb_image.data, w, h, bytes_per_line, QImage.Format_RGB888)
                p = convert_to_qt_format.scaled(521, 341)
                self.frame_signal.emit(p)

    def stop(self):
        self.running = False
        self.camera.release()
