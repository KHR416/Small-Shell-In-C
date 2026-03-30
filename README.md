# Small Shell in C

POSIX shell의 핵심 동작을 C로 구현한 팀 프로젝트입니다. 
이 프로젝트에서는 기능 구현 자체뿐 아니라, 모듈 경계 정의, 리뷰 기반 통합, 회귀 방지 중심의 협업 프로세스를 중점적으로 운영했습니다.

## Team and Repository

- Original Repository: https://github.com/NormalizationOfMinishell/Small-Shell-In-C
- Team: KHR416, Saususge

## Project Summary

Small Shell in C는 커맨드 입력을 해석하고 실행하는 간단한 셸입니다.
토큰화, 파싱, AST 구성, 실행 레이어, built-in 명령, 환경 변수 처리, 시그널 처리까지 셸의 핵심 경로를 구현했습니다.

협업 측면에서의 핵심 목표는 다음이었습니다.
- 파이프라인 단위로 모듈 책임을 명확히 분리
- 충돌이 잦은 구간(파서/실행/시그널)을 인터페이스 중심으로 합의
- PR/리뷰/테스트 루틴으로 통합 리스크를 낮춤

## Tech Stack

- C
- GNU Readline

선택 이유:
- 시스템 콜/프로세스 제어를 직접 다루기 위해 적합
- Readline으로 인터랙티브 셸 입력/히스토리를 구현

## My Role and Contributions

이 프로젝트에서는 역할을 고정하기보다, 팀의 병목 구간을 우선순위로 해결하는 방식으로 기여했습니다.

### Main Contributions
- Parser and token stream refactoring
  - 토큰 스트림 분석 경로를 정리하고 파싱/실행 경계를 명확화
  - 관련 이슈 예시: tokenizing with "$", token stream 분석 리팩터링
- Built-in and shell behavior alignment
  - bash 동작과의 차이를 줄이기 위해 built-in 동작 및 exit status 케이스 보완
  - 관련 이슈 예시: echo -n, ms_export invalid identifier, exit behavior
- Runtime stability fixes
  - PATH unset 이후 실행 크래시, redirection, heredoc/pipeline 등 런타임 오류 케이스 개선
  - 관련 이슈 예시: exec after unset PATH, redirection bug on pipe_seg_exec
- Codebase maintenance and normalization
  - norm/구조 리팩터링 및 모듈 경계 재정비
  - 관련 이슈 예시: refactoring codes for norm standard

### Collaborative Contributions
- 공통 인터페이스 합의
  - parser, AST, exec 레이어의 함수 경계와 자료구조 규약 조율
- 코드 리뷰 참여
  - PR 단위 변경 영향 점검, 회귀 가능성 피드백, 수정 요청 반영
- 통합 과정 지원
  - 브랜치 병합 시 충돌 구간 정리 및 테스트 루틴 점검

## 협업 및 리뷰 근거

저장소 활동 로그를 보면, 이 프로젝트는 이슈 기반으로 작업을 관리하고 리뷰를 거쳐 병합하는 협업 흐름으로 운영되었습니다.

- 닫힌 Pull Request: 39
- 닫힌 Issue: 34
- PR 병합 과정에서 아래와 같은 리뷰 게이트가 확인되었습니다.
  - review required before merging
  - review requesting changes
- 이슈 라벨은 bug/enhancement/todo/help wanted가 혼합되어 있어,
  기획, 버그 수정, 리팩터링이 모두 이슈 단위로 추적되었음을 보여줍니다.

닫힌 이슈에서 반복적으로 다뤄진 주제:
- 토크나이징 및 파서 정확성
- PATH/unset 이후 실행 안정성
- redirection/pipeline 경계 케이스
- wildcard(glob) 동작 및 함수 시그니처 논의
- bash와의 동작 정합성(signal/exit/built-in)

## Architecture

Input line
-> Tokenizer
-> Token stream validation
-> AST construction
-> AST analysis
-> Command Execution Unit parsing
-> Execution (builtin/external, redirection, env)

프로젝트 구조 참고:
- 헤더: include/
- 핵심 구현: src/
- 보너스 구현: bonus_src/

## Technical Decisions / Troubleshooting

### A. Parser-Executor 경계
문제:
- 파싱 단계와 실행 단계의 책임이 섞이면 디버깅 비용이 급격히 증가

결정:
- 실행에 필요한 단위를 분리하고, 파싱 결과를 명시적으로 전달

효과:
- 오류 위치 추적이 빨라지고, 테스트 범위를 레이어별로 나눌 수 있게 됨

### B. 상태 관리와 버퍼 전략
문제:
- 셸은 입력/토큰/환경 변수/임시 상태가 많아 메모리 누수가 발생하기 쉬움

결정:
- 버퍼/전역 상태 구조를 명확히 분리하고, 정리 루틴을 일관되게 적용

효과:
- 기능 추가 시 누수/정리 누락 리스크 감소

### C. 시그널과 인터랙션
문제:
- 인터랙티브 셸에서 시그널 처리와 프롬프트 동작이 쉽게 꼬임

결정:
- 시그널 처리 경로를 별도 유틸/헬퍼로 분리

효과:
- 사용자 입력 경험과 종료 코드 처리 일관성 향상

## Build and Run

### Build
```bash
make bonus
```

### Run
```bash
./minishell
```

### Clean
```bash
make clean
make fclean
```

## Portfolio Notes

- 이 README는 포트폴리오 공개용입니다.
- 협업 증빙은 closed PR/Issue 로그를 기준으로 요약했습니다.
