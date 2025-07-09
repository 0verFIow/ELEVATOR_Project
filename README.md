# STM32 + FreeRTOS Elevator Project

본 프로젝트는 **STM32** MCU와 **FreeRTOS**를 이용하여  
단순 4층 엘리베이터(버튼/스텝모터/LED/FND/센서 등) 제어를 구현한 예제입니다.

---

## 📋 프로젝트 설명

- **플랫폼:** STM32 (CubeIDE, FreeRTOS 기반)
- **주요 기능:**
  - 스텝모터를 이용한 엘리베이터 모형 제어
  - 버튼 입력으로 원하는 층수 선택 및 큐 관리 (circular queue)
  - 각 층 도착 감지는 EXTI(외부 인터럽트)로 체크
  - FND(7세그먼트) 및 LED, 부저 등으로 상태 표시
  - FreeRTOS Task 분할 (모터, 버튼, 디스플레이 등)

---

## 🗂️ 주요 파일

- **Core/Src**
  - `main.c` : FreeRTOS Task 생성 및 전체 흐름
  - `stepmotor.c` : 스텝모터 구동, 엘리베이터 동작 로직
  - `button.c` : 버튼 입력 처리, 큐 삽입
  - `fnd.c` : FND(7세그먼트) 시계/표시
  - `extint.c` : 외부 인터럽트(층 도착 감지)
  - `circularQueue.c` : 층 요청 큐 관리

- **Core/Inc**
  - 각 소스 파일에 대응하는 헤더파일
  - 시스템 전역 변수/상수 선언(`extern.h` 등)

---

## 🔧 회로 및 연결

- **스텝모터** : X, Y핀 (ex: PB0~PB3)
- **버튼** : PC0~PC3 (1~4층 호출)
- **FND** : GPIOB, 74HC595 시프트 레지스터 사용
- **층 도착 감지** : PA0, PB1, PB2, PB4 등(외부 인터럽트)
- (정확한 핀맵은 CubeMX 혹은 main.h/코드 주석 참고)

---

## 🚦 FreeRTOS Task 구조

- `StartDefaultTask` : 스텝모터 제어/동작 주기적 체크
- `StartTask02` : 버튼 입력 및 요청 큐 관리
- `StartTask03` : FND 및 dotmatrix 등 표시 주기적 업데이트

---

## ⚙️ 빌드 & 실행법

1. STM32CubeIDE에서 `.ioc` 파일로 프로젝트 오픈
2. 빌드 후 보드에 업로드
3. 실제 버튼/센서/모터가 연결된 보드에서 테스트

---

## 📝 코드 하이라이트

- **circularQueue.c**
  - 원형 큐로 엘리베이터 요청 순서 처리
- **stepmotor.c**
  - 엘리베이터 실제 이동 로직(상태머신)
- **button.c**
  - 버튼 이벤트, LED 출력, 부저
- **extint.c**
  - 각 층 도착시 인터럽트로 동작 종료/큐 pop

---

## 💡 참고 및 주의

- FreeRTOS 및 HAL 라이브러리 필수 (CubeMX 생성 환경)
- 하드웨어 결선에 따라 코드 일부 수정 필요
- 핀맵, 부품 스펙 등은 주석/코드/회로도 참고

---

## 👤 작성자 및 문의

- 작성자: OverFlow (이웅)
- 문의/이슈: [깃허브 Issues](https://github.com/OverFlow/ELEVATOR_Project/issues)

