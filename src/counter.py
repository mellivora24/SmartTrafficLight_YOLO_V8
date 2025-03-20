import utils
from ultralytics import YOLO

class Counter:
    def __init__(self):
        self.model = YOLO(utils.resource_path('./res/best.pt'))

    def count_vehicles_from_image(self, image):
        results = self.model(image)

        count = 0
        for result in results.xyxy[0]:
            if result[5] == 2:
                count += 1

        return count

if __name__ == "__main__":
    import cv2
    camera = cv2.VideoCapture(0)

    counter = Counter()
    while True:
        ret, frame = camera.read()
        count = counter.count_vehicles_from_image(frame)
        print(count)
        cv2.imshow("Test counter function", frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    camera.release()
    cv2.destroyAllWindows()
