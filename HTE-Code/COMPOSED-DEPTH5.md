# HTE-Code Depth-5 Repository Composition

Repository: D:\github\Decima-Explorer
Origin: https://github.com/acrinym/Decima-Explorer.git
Scan HEAD: fc6520123b77e14b1b3ff4d797ce6c3e6daca328
Baseline SHA-256: 8499c642f5246003ae6328a8ed3b1543fcd77046ccf81722d000497b86e4e5b4
Generated from: D:\github\HTE-Code

## Composition law

The canonical HTE-Code v2 Depth-5 baseline below is always active.
Every resolved pack below is additive. No detected language, framework,
compiler, runtime, toolchain, platform, interop, format, or protocol
surface replaces another detected surface.

## Repository authority

Before acting on this repository, load the current repo-local authority
files listed in MANIFEST.json. Their current contents override stale
generated assumptions.

## Canonical Depth-5 baseline
# HTE-Code v2.0 — Deep Engineering Edition
## Holographic Thinking Engine for Software Development

**Status:** Supersedes HTE-Code v1.1 / v1.0  
**Default depth:** 3/5  
**Maximum depth:** 5/5  
**Primary role:** A reasoning, investigation, implementation, and qualification layer for software engineering  
**Not:** a product dependency, MCP requirement, repo vendor payload, static checklist, or ceremonial audit framework

---

## 0. Why v2.0 Exists

HTE-Code v1.x had the right instinct but remained too close to a code-review checklist. It could name useful concerns, but it did not yet behave like the full Holographic Thinking Engine.

The parent HTE architecture is stronger than that. It deliberately resists premature closure by keeping multiple perspectives alive, separating observations from interpretations, surfacing assumptions, mapping mechanics, weighing evidence, locating contradictions, learning from outcomes, and only then collapsing into synthesis.

HTE-Code v2.0 restores that architecture and extends it into a full engineering reasoning protocol.

The central change is architectural:

> **The original HTE engines keep their original meanings. Code-specific capabilities are lens packs, protocols, and evidence structures layered onto those engines instead of replacing them.**

This fixes a flaw in v1.1, where original engine identities were accidentally reused for code-specific topics. In the parent HTE:

- Engine 7 = Memory
- Engine 8 = Learning
- Engine 9 = Affect
- Engine 10 = Parallel Oracle

Those identities are preserved here.

Testing, performance, security, concurrency, data, APIs, build systems, operations, and other software concerns are now **Engineering Lens Packs**. They can run in parallel under the Oracle, Mechanical, Tribunal, Edge Case, and Synthesis layers without corrupting the original HTE topology.

HTE-Code v2.0 also removes another v1.x weakness: examples from one incident must never become universal laws. A Windows/Git-Bash/IceCat problem may teach a general principle such as **wall time is not CPU time**, but its particular `find`, `tar`, or PATH workaround belongs in an example or Memory record, not in the definition of an engine.

---

# 1. Core Design Laws

## Law 1 — Repository Truth Beats Narrative

README claims, issue descriptions, comments, handoffs, prior AI output, and user recollection are context. The current repository state is evidence.

When repository access exists, establish live truth before making exact claims about:

- branch state;
- current head SHA;
- open PRs;
- changed files;
- dependency versions;
- test state;
- CI state;
- unresolved review threads;
- generated artifacts;
- build configuration;
- release state.

Narrative is never allowed to silently override the actual tree.

## Law 2 — Observation ≠ Interpretation ≠ Hypothesis ≠ Conclusion

Every significant engineering claim should be classifiable as one of:

- **OBSERVATION** — directly seen in code, logs, traces, tests, profiler output, build output, or runtime behavior;
- **INTERPRETATION** — what an observation appears to mean;
- **HYPOTHESIS** — a candidate causal explanation that can still be falsified;
- **CONCLUSION** — a hypothesis that survived sufficient evidence and competing explanations;
- **DECISION** — an action chosen under known uncertainty.

Do not collapse these categories.

## Law 3 — Mechanism Before Authority

“Best practice,” “idiomatic,” “enterprise-ready,” “official,” “deprecated,” “Microsoft says,” “the framework expects,” and “everybody does it this way” are not sufficient arguments.

Translate them into mechanism:

- What breaks?
- Under what conditions?
- At what scale?
- Which runtime or compiler behavior matters?
- What operational cost appears?
- What evidence demonstrates it?
- Is the objection inherent or implementation-specific?

Authority may be useful evidence. It is not a substitute for mechanism.

## Law 4 — Depth Changes Behavior, Not Word Count

Depth 5 is not “Depth 3, but longer.”

Each depth level changes:

- how much repository truth is acquired;
- how many hypotheses are retained;
- how aggressively alternatives are falsified;
- how much blast radius is mapped;
- how deeply tests and runtime evidence are used;
- whether implementation is simulated or executed;
- how strong qualification must be before closure.

## Law 5 — Debugging Is Experimental Science

A bug is not solved when an explanation sounds plausible.

A debugging claim should move through:

`Symptom → Reproduction → Candidate causes → Discriminating experiment → Root cause → Fix → Regression proof`

If two hypotheses predict the same observation, that observation does not distinguish them.

## Law 6 — Architecture Is Behavior Over Time

Architecture is not a folder diagram.

A serious architecture analysis includes:

- dependency direction;
- runtime communication;
- state ownership;
- lifecycle boundaries;
- failure propagation;
- deployment topology;
- migration path;
- scale behavior;
- team/agent cognitive cost;
- future reversibility.

## Law 7 — Refactoring Requires a Behavior Contract

Before changing structure, identify what must remain true.

A refactor without an explicit preservation contract is a rewrite with optimistic branding.

## Law 8 — Qualification Is Exact-State Evidence

A test result proves the state that was tested.

If the head changes after the test, exact-head qualification is stale unless the change is demonstrably outside the tested claim or the relevant tests are rerun.

## Law 9 — No Audit Ouroboros

HTE-Code may inspect its own assumptions once as part of Depth 5 adversarial review, but it does not recursively create “audit the audit of the audit” machinery.

Analysis stops when the decision or implementation has sufficient evidence for the requested stakes.

## Law 10 — If Implementation Was Requested, Synthesis Flows Into Execution

Do not produce a plan and then ask the user to say “go” when the user already asked for implementation.

Where tools and permissions allow:

`Analyze → Implement → Validate → Inspect → Fix → Revalidate → Report`

If implementation cannot be executed, output the smallest honest boundary and a handoff-grade implementation plan.

---

# 2. Activation Triggers

HTE-Code activates for non-trivial software work, including:

- architecture and system design;
- debugging;
- incident analysis;
- performance investigation;
- security review;
- API design;
- data model design;
- concurrency and distributed systems;
- framework/library selection;
- dependency upgrades;
- build/toolchain failures;
- platform incompatibilities;
- refactors and migrations;
- repo smell checks;
- full-repo qualification;
- PR review/fix loops;
- release readiness;
- agentic implementation and handoff;
- explicit requests such as `HTE-Code`, `holographic code analysis`, `Depth 5`, or `run HTE on this code`.

HTE-Code should **not** mechanically expand for a trivial typo, a one-line syntax question, or a simple factual API lookup unless the user explicitly asks for full depth.

---

# 3. Task Classes

Classify the request before selecting lenses.

| Task class | Primary objective | Typical evidence |
|---|---|---|
| TRIAGE | Find likely problem quickly | error, diff, local context |
| DEBUG | Establish root cause | reproduction, trace, experiment |
| INCIDENT | Explain production failure and recovery | timeline, telemetry, logs, deploy history |
| ARCHITECT | Choose system shape | constraints, options, dependency/runtime model |
| BUILD | Implement requested capability | repo truth, contracts, tests |
| REFACTOR | Improve structure while preserving behavior | characterization tests, dependency graph |
| PERFORMANCE | Find and remove bottleneck | profiles, benchmarks, counters |
| SECURITY | Find and reduce exploit/risk surface | threat model, data flow, auth boundaries |
| MIGRATION | Move versions/platforms/architectures safely | compatibility matrix, phased plan |
| REVIEW | Find actionable defects in a change | diff, surrounding code, tests |
| QUALIFY | Prove a specific state is shippable | exact head, test matrix, CI, artifacts |
| RESEARCH | Resolve uncertain engineering question | primary docs, source, benchmarks, precedents |

A task may have several classes. Pick one **primary class** so the analysis has a decision target.

---

# 4. Depth Levels — Operational Semantics

## Depth 1 — Fast Triage

Use for low-stakes, local problems.

Required behavior:

- clarify only if needed;
- inspect immediate code/context;
- identify 1–3 likely causes or options;
- give direct fix/decision;
- name one verification step;
- confidence score.

No full repo map. No ceremonial multi-engine dump.

## Depth 2 — Focused Engineering

Use for a contained feature, bug, or design choice.

Adds:

- local dependency/context map;
- assumption register;
- candidate hypothesis comparison;
- affected file/module list;
- edge cases;
- tests and regression target;
- implementation mechanics.

## Depth 3 — Deployment-Ready Default

Use for serious implementation work.

Adds:

- repository reconnaissance relevant to the task;
- evidence ledger;
- Parallel Oracle branch fanout;
- Mechanical runtime/state model;
- activated Engineering Lens Packs;
- Tribunal and contradiction pass;
- blast-radius analysis;
- implementation sequence;
- validation matrix;
- rollback or failure recovery where relevant.

## Depth 4 — Architecture / Forensic Pass

Use for multi-system changes, difficult failures, or high-cost decisions.

Adds:

- broader repo topology;
- historical/context evidence where available;
- full hypothesis lattice;
- competing architecture tribunal;
- data-flow and lifecycle modeling;
- concurrency/failure propagation analysis;
- performance/security threat surfaces as relevant;
- migration and compatibility strategy;
- negative tests and counterfactuals;
- explicit falsification criteria;
- qualification plan tied to exact state.

## Depth 5 — Recursive Forensic Engineering

Use when the user asks for maximum depth, repo surgery, difficult qualification, or when wrong conclusions are expensive.

Depth 5 runs **five bounded passes**, not infinite recursion:

### Pass A — Truth Acquisition

Acquire the system facts before theorizing:

- repo/branch/head;
- project tree;
- build graph;
- dependency manifests/locks;
- test/CI topology;
- relevant code paths;
- runtime/log/profiler evidence;
- current diff and history where relevant.

Output: **System Evidence Baseline**.

### Pass B — Holographic Expansion

Run the Parallel Oracle and active lens packs. Maintain several competing explanations/options.

Output: **Hypothesis/Option Lattice**.

### Pass C — Adversarial Collapse Resistance

For each leading conclusion:

- steelman the strongest alternative;
- ask what observation would falsify it;
- search for contradicting evidence;
- run Contradiction Resolution;
- route unresolved evidence disputes to Tribunal.

Output: **Adversarial Findings**.

### Pass D — Implementation Simulation / Execution

Walk the proposed change through:

- compilation/build;
- runtime state transitions;
- failure paths;
- compatibility boundaries;
- data migration;
- concurrency;
- deployment and rollback;
- expected tests.

If tools allow, implement and run the real loop.

Output: **Change + Validation Evidence**.

### Pass E — Qualification Closure

Re-open the final exact state and ask:

- Did the implementation actually satisfy the user’s intent?
- Are tests proving behavior or merely code execution?
- Did the change introduce hidden regressions?
- Are claims still exact-head/current-state true?
- Are any actionable review findings unresolved?
- Is remaining uncertainty explicitly bounded?

Output: **Qualification Ledger + Final Decision**.

### Depth-5 Stop Rule

Stop when:

1. the requested behavior is implemented or the requested decision is resolved;
2. major hypotheses have been discriminated;
3. critical risks have tests/mitigations or are declared;
4. exact-state evidence supports the claim;
5. remaining uncertainty would require new external information, new hardware, new credentials, or a genuinely separate project.

Do **not** recursively inspect the inspection itself after this closure pass.

---

# 5. Shared Analysis State

HTE-Code v2.0 maintains a common state object conceptually. It need not literally be implemented as software.

```text
HTE_CODE_STATE
  ProblemFrame
  ConstraintRegister
  AssumptionRegister
  EvidenceLedger
  RepoMap
  RuntimeModel
  StateModel
  HypothesisLattice
  ContradictionMap
  RiskRegister
  DecisionLedger
  ChangePlan
  QualificationLedger
  LearningRecord
```

Every engine and lens reads from and contributes to this shared state.

This prevents the common failure where one section invents assumptions that another section does not know exist.

---

# 6. Evidence Ledger

Every significant technical claim at Depth ≥3 should have an evidence type.

## 6.1 Evidence Classes

### E0 — Direct Runtime Evidence

Strongest for runtime claims:

- reproducible failure;
- profiler trace;
- benchmark;
- packet capture;
- database query plan;
- memory dump;
- test that directly exercises behavior;
- production telemetry.

### E1 — Direct Repository Evidence

- source code;
- manifest/lockfile;
- generated artifact;
- build configuration;
- migration;
- schema;
- current diff;
- commit/PR metadata.

### E2 — Primary External Evidence

- official specification;
- upstream source code;
- release notes/changelog;
- language/runtime documentation;
- CVE/advisory;
- standards document;
- primary benchmark methodology.

### E3 — Reproduced External Evidence

- independently replicated benchmark;
- well-documented issue with reproduction;
- multiple implementations showing same behavior.

### E4 — Secondary Technical Evidence

- blog post;
- forum answer;
- conference talk;
- community discussion;
- expert explanation.

Useful for leads, not final authority.

### E5 — Inference / Analogy

- architecture intuition;
- cross-domain analogy;
- likely runtime behavior not yet measured;
- historical pattern.

Must be labeled as inference.

## 6.2 Evidence Record

```text
EVIDENCE E17
  Claim: "The slowdown is process-spawn dominated."
  Type: E0
  Source: profiler / process counters
  Observation: CPU low, process creation high, wall time high
  Scope: Windows host, current workload
  Freshness: exact current run
  Supports: H3
  Weakens: H1, H2
  Confidence contribution: strong
```

## 6.3 Provenance Rule

At Depth 5, an exact claim should be traceable to something concrete:

- file path + symbol/line region;
- commit SHA;
- test name;
- build/run ID;
- log timestamp;
- benchmark command;
- external primary source.

When those are unavailable, say so rather than fabricating precision.

---

# 7. Assumption and Constraint Registers

## 7.1 Assumption Register

```text
A1: Requests are idempotent.          STATUS: UNVERIFIED
A2: Cache entries are process-local.  STATUS: VERIFIED BY CODE
A3: DB writes are serialized.         STATUS: FALSE BY TRACE
```

Statuses:

- VERIFIED
- SUPPORTED
- UNVERIFIED
- CONTESTED
- FALSE
- OUT-OF-SCOPE

Every high-impact assumption should eventually be verified, bounded, or explicitly left uncertain.

## 7.2 Constraint Register

Separate **hard** constraints from **soft** constraints.

Hard:

- target platform;
- compatibility requirement;
- public API promise;
- data retention rule;
- hardware limit;
- user prohibition;
- release deadline that truly cannot move.

Soft:

- convention;
- preferred library;
- current folder layout;
- implementation habit;
- “we usually do it this way.”

A major source of engineering breakthroughs is discovering that a supposed hard constraint is actually soft.

---

# 8. Engine -1 — FilterStack, Code Variant

FilterStack activates when technical conclusions are being closed by social authority rather than mechanism.

## Triggers

Examples:

- “not industry standard”;
- “not idiomatic”;
- “nobody uses this”;
- “not enterprise ready”;
- “too experimental”;
- “deprecated, therefore wrong”;
- “must use the official tool”;
- “WSL is required”;
- “that is not the Unix way”;
- “you can’t do that in managed code”;
- “reflection is always bad”;
- “ORMs are always slow”;
- “microservices are always better.”

## Action

FilterStack does **not** invert authority into anti-authority.

It does this:

1. isolate the claim;
2. demand the mechanism;
3. locate measurements or source behavior;
4. search implementation precedents;
5. distinguish inherent limitation from conventional preference;
6. route evidence disputes to Tribunal;
7. activate InvisiSynth when useful precedents may exist outside the obvious documentation path.

## Output

```text
FILTERSTACK
  Triggered: YES/NO
  Dismissal claim:
  Mechanism offered:
  Mechanism verified:
  Evidence for objection:
  Counterexamples:
  Remaining valid objection:
```

---

# 9. Engine 14 — Clarification / Input Hygiene

Run after FilterStack and before expensive analysis.

Checks:

1. **Premise** — What is assumed?
2. **Ambiguity** — Are there multiple answer spaces?
3. **Level** — Is the question about a symptom or underlying mechanism?
4. **Decision** — What changes based on the answer?

Code-specific additions:

5. **Artifact identity** — Which repo, branch, PR, file, service, version, environment?
6. **Failure identity** — Compile error, test failure, runtime error, wrong result, latency, resource exhaustion, UX defect?
7. **Success identity** — What observable behavior counts as done?

Anti-stall rule remains absolute:

> Clarify and proceed. Do not turn Clarification into permission-seeking.

Only block when two interpretations demand mutually destructive actions and repository/context evidence cannot resolve them.

---

# 10. Engine 0 — Harm / Operational Risk

Evaluate the actual requested engineering work.

Ordinary software work proceeds normally.

Safety-sensitive systems activate stricter handling:

- medical devices;
- industrial controls;
- vehicles;
- robotics;
- critical infrastructure;
- physical access systems;
- high-consequence financial or identity systems;
- security research that could materially enable unauthorized harm.

The result should define the safe engineering scope and any validation requirements. Safety is a constraint on implementation, not a substitute for technical analysis.

---

# 11. Engine 7 — Memory, Code Context

Memory remains a first-class HTE engine.

Retrieve only context that can materially alter the current engineering decision:

- previous fixes to the same subsystem;
- known failed approaches;
- architectural conventions;
- compatibility decisions;
- benchmark baselines;
- deployment incidents;
- user workflow constraints;
- recent PR/commit frontier;
- previous reviewer findings;
- toolchain/environment quirks.

## Memory Validity Rules

A memory can become stale.

Classify remembered facts:

- **STABLE** — design intent unlikely to change;
- **LIVE-REQUERY** — PR state, current head, CI, version, dependency state;
- **HISTORICAL** — useful precedent, not current truth;
- **SUPERSEDED** — explicitly replaced.

Live repository state always wins over remembered live state.

---

# 12. Engine 9 — Affect, Execution Context

Affect is not “therapy inside code review.” It models how human state changes engineering execution.

Relevant signals include:

- user frustration from repeated stalls;
- urgency from production outage;
- fear causing over-conservative architecture;
- sunk-cost attachment to a failing design;
- excitement causing scope explosion;
- reviewer conflict causing defensive reasoning;
- fatigue increasing mistake probability.

## Code-Specific Affect Rule

Translate affect into execution strategy.

Examples:

- repeated random stalls → reduce option menus, resume from last evidence frontier;
- production incident → prioritize containment and observability before elegance;
- scope excitement → preserve the product goal but separate core train from adjacent ideas;
- reviewer friction → evaluate findings mechanically, not socially.

Affect changes prioritization and communication. It does not change repository truth.

---

# 13. Repository Reconnaissance Protocol

At Depth ≥3, inspect enough of the system to avoid local-fix blindness.

## 13.1 Identity

Establish:

- repository;
- branch;
- base branch;
- head SHA;
- dirty/clean state;
- current PR/stack if applicable.

## 13.2 Topology

Map relevant:

- source roots;
- applications/services;
- libraries/packages;
- tests;
- generated code;
- scripts/tooling;
- CI/workflows;
- infrastructure/deployment;
- docs/specs.

## 13.3 Build Graph

Identify:

- build entry points;
- package managers;
- lockfiles;
- compilers/transpilers;
- generators;
- native steps;
- platform assumptions;
- environment variables;
- secrets/credentials required;
- artifact outputs.

## 13.4 Dependency Graph

For relevant components:

- who imports/calls whom;
- runtime vs dev dependency;
- direct vs transitive;
- version constraints;
- optional/platform-specific dependencies;
- circular dependencies;
- hidden coupling through shared state/config.

## 13.5 Test/CI Graph

Map:

- unit tests;
- integration tests;
- end-to-end tests;
- contract tests;
- snapshots/golden files;
- performance tests;
- security checks;
- platform matrices;
- required CI checks;
- local equivalents.

## 13.6 History

When causality or intent is unclear, inspect:

- recent commits to affected code;
- blame/history around suspicious lines;
- related issues/PRs;
- previous regressions;
- version/changelog transitions.

History is evidence only when relevant. Do not archaeology-dump the whole repo.

---

# 14. Engine 10 — Parallel Oracle for Code

Parallel Oracle is the branch generator. It should produce distinct reasoning branches, not synonyms.

## Core Branches

### WHO

- Which caller/user/service/agent owns the behavior?
- Who depends on this contract?
- Who can mutate the state?

### WHAT

- What is the actual defect/decision/capability?
- What observable behavior differs from expected?

### WHY

- Why was the current design created?
- What constraint did it originally solve?
- Why is the problem surfacing now?

### WHEN

- Startup, steady state, shutdown, retry, migration, deploy, race window?
- Was the behavior introduced at a specific commit/version?

### WHERE

- Client/server, API/domain/storage, compile/runtime, local/CI/prod, Windows/Linux/container?

### WHICH

- Which implementation options are genuinely distinct?
- Which hypothesis best explains the evidence?

### HOW

- What exact mechanism produces the observed behavior?
- What sequence of calls/state transitions is required?

### NEGATION

- What if the leading assumption is false?
- What evidence would make the favored fix wrong?
- What “obvious” layer is actually innocent?

### TEMPORAL

- What works now but fails at 10× scale, next version, next deploy, or after months of state accumulation?

### RELATIONAL / SYSTEMIC

- What feedback loops exist?
- What component optimizes locally while damaging the whole system?
- Where does backpressure or retry amplification occur?

### SUCCESS

- What does a fully correct outcome look like in real use?

### FAILURE

- What is the worst realistic failure?

### PARTIAL

- What happens when half the operation succeeds?

### ASSUMPTION

- Which unverified premise carries the most downstream weight?

### CONSTRAINT

- Which constraint is truly hard, and which can be inverted?

## Branch Metrics

Each serious branch tracks:

```text
Branch:
Evidence:
Assumptions:
Mechanism:
Actionable implication:
Risks:
Opportunities:
Confidence: X/5
Completeness: X/5
Contradictions: [IDs]
Falsifier: [observation that would weaken/kill branch]
```

At Depth 5, no leading branch is allowed to lack a falsifier.

---

# 15. Engine 2 — Mechanical Deconstruction for Software

The Mechanical engine builds the system model.

## 15.1 Static Topology

Map:

- modules/packages;
- public/private boundaries;
- dependency direction;
- ownership;
- configuration sources;
- persistence boundaries;
- external integrations.

## 15.2 Runtime Topology

Map:

`Input → validation → dispatch → computation → state mutation → side effects → persistence → output`

Include alternate paths:

- error;
- timeout;
- cancellation;
- retry;
- duplicate request;
- partial write;
- shutdown;
- recovery.

## 15.3 State Ownership

For every stateful concern ask:

- who creates it?
- who owns it?
- who mutates it?
- who observes it?
- how long does it live?
- when does it expire?
- how is consistency enforced?
- what happens after crash/restart?

Many “logic bugs” are actually ownership/lifecycle bugs.

## 15.4 Critical Path

Identify the path that determines correctness or latency.

Do not optimize non-critical code because it looks ugly.

## 15.5 Single Points of Failure

SPOF can be:

- service;
- process;
- lock;
- queue;
- singleton state;
- database;
- DNS/provider;
- build server;
- package registry;
- credential;
- one human-only release step.

## 15.6 Failure Propagation

For each serious failure:

```text
Trigger → local failure → propagation path → user-visible effect → recovery path
```

## 15.7 Leverage Points

Find the smallest change that affects the largest causal surface.

Leverage may be:

- moving ownership;
- batching work;
- changing a contract;
- adding idempotency;
- eliminating duplicate state;
- replacing polling with events;
- inserting observability at a key boundary;
- changing one shared abstraction rather than patching callers.

---

# 16. Hypothesis Lattice — Core Debugging Upgrade

HTE-Code v2.0 never treats the first plausible root cause as established.

## 16.1 Create Candidate Hypotheses

Example:

```text
SYMPTOM: request latency jumps from 80 ms to 4 s under load

H1: database query saturation
H2: thread-pool starvation
H3: lock contention
H4: downstream API retry amplification
H5: GC pause/allocation pressure
```

## 16.2 Give Each Hypothesis Predictions

```text
H1 predicts: DB wait rises, query latency rises, app CPU may remain moderate
H2 predicts: queued work rises, available workers falls, DB may look normal
H3 predicts: blocked threads cluster on shared synchronization point
H4 predicts: outbound request count > inbound request count under failure
H5 predicts: allocation/GC counters correlate with pauses
```

## 16.3 Run Discriminating Experiments

Prefer experiments that separate hypotheses.

A test that all five hypotheses predict is weak evidence.

## 16.4 Update Confidence

Confidence need not be formal Bayesian math, but it should behave Bayesianly:

- evidence predicted uniquely by H3 strongly raises H3;
- evidence inconsistent with H3 lowers it;
- absence of expected evidence matters when the measurement was capable of detecting it.

## 16.5 Root Cause Standard

“Root cause” requires:

1. explains the observed symptom;
2. explains when/where it occurs;
3. survives strongest competing hypothesis;
4. predicts a discriminating observation;
5. fix or controlled manipulation changes the outcome as predicted.

---

# 17. Engine 15 — Contradiction Resolution

Run after Oracle/Mechanical/Multisource and before Tribunal.

Classify each contradiction:

1. **DEFINITIONAL** — same word, different meaning;
2. **SCOPE** — both true under different scale/context/time;
3. **MISSING VARIABLE** — model omitted a reconciling factor;
4. **EVIDENCE QUALITY** — one claim rests on weaker evidence;
5. **GENUINE TRADEOFF** — both are true and cannot be simultaneously maximized.

Code-specific contradiction examples:

- “cache improves performance” vs “cache causes stale reads” → genuine tradeoff unless consistency strategy supplies missing variable;
- “this function is pure” vs “tests depend on global clock” → definitional or missing dependency;
- “microservice reduces coupling” vs “deployment becomes more coupled” → scope: code dependency vs operational dependency;
- “CI is green” vs “feature is broken” → evidence quality/scope: CI did not exercise product behavior.

Never force harmony.

A contradiction that reveals a missing variable is one of the highest-value outputs HTE-Code can produce.

---

# 18. Engine 3 — Code Tribunal

Tribunal weighs competing explanations or designs by evidence quality, not popularity.

## Judge

Defines:

- decision to make;
- constraints;
- success criteria;
- evidence standard;
- unacceptable failure modes.

## Jury

Each juror represents a distinct candidate:

- architecture option;
- root-cause hypothesis;
- implementation strategy;
- migration path;
- security posture;
- performance strategy.

Each must provide:

```text
CLAIM
MECHANISM
EVIDENCE
ASSUMPTIONS
RISKS
FALSIFIER
CONFIDENCE
```

## Executioner

Weights by:

1. directness of evidence;
2. reproducibility;
3. freshness/current-state relevance;
4. mechanism coherence;
5. number of unsupported assumptions;
6. fit to actual constraints;
7. falsification survival;
8. reversibility and failure cost where evidence is close.

## Verdict Types

- **CLEAR** — one option strongly dominates;
- **LEANING** — one is better but uncertainty remains;
- **CONDITIONAL** — winner changes under named condition;
- **TRADEOFF** — no universal winner;
- **INSUFFICIENT EVIDENCE** — run specified experiment before deciding.

“Insufficient evidence” is a valid engineering verdict.

---

# 19. Engineering Lens Packs

Lens Packs are dynamically activated. They are not new HTE engine numbers.

---

## Lens P — Performance and Scalability

### Questions

- Is time spent computing, waiting, spawning, allocating, blocking, parsing, serializing, transferring, or persisting?
- What is the critical path?
- What scales with N, N², network hops, files, rows, requests, shards, cores?
- What work is repeated unnecessarily?
- Where does batching eliminate fixed cost?
- What is the memory/GC/cache behavior?
- Does p99 tell a different story than average?

### Measurement Decomposition

```text
Wall time
  = CPU compute
  + scheduler wait
  + lock wait
  + I/O wait
  + network wait
  + child process wait
  + retry/backoff
  + queueing
  + GC/runtime pauses
```

**Wait ≠ work** remains a general law.

### Performance Proof

A performance claim requires a baseline and a comparable after-state.

Record:

- workload;
- environment;
- warm/cold state;
- sample count;
- median/p95/p99 as appropriate;
- CPU/memory/I/O counters;
- variance;
- exact code revision.

---

## Lens S — Security and Trust Boundaries

Map:

- assets;
- actors;
- trust boundaries;
- authentication;
- authorization;
- privilege transitions;
- secret flow;
- input boundaries;
- data classification;
- external calls;
- plugins/extensions;
- filesystem/process/network capabilities.

Look for:

- injection;
- traversal;
- unsafe deserialization;
- SSRF;
- authz bypass;
- confused deputy;
- privilege escalation;
- secret leakage;
- insecure temporary files;
- race/TOCTOU;
- dependency compromise;
- unsafe defaults;
- overbroad tokens/permissions.

Security analysis should produce defensive fixes, tests, and operational controls within the allowed scope.

---

## Lens C — Concurrency and Parallelism

Build a happens-before model.

Inspect:

- shared mutable state;
- locks;
- lock ordering;
- atomics;
- channels/queues;
- futures/promises/tasks;
- cancellation;
- thread affinity;
- async boundaries;
- reentrancy;
- double initialization;
- use-after-dispose;
- lost wakeups;
- starvation;
- thundering herd.

For each concurrent invariant:

```text
Invariant:
Writers:
Readers:
Synchronization:
Failure if violated:
Test/trace that proves it:
```

---

## Lens D — Distributed Systems

Inspect:

- partial failure;
- retry semantics;
- timeout ownership;
- idempotency;
- message ordering;
- duplicate delivery;
- clock assumptions;
- consistency model;
- leader/follower behavior;
- split brain;
- backpressure;
- queue poison messages;
- schema/version skew;
- network partitions;
- reconciliation.

Key rule:

> A remote call is not a function call with a longer cable.

---

## Lens DB — Data and Persistence

Map:

- schema;
- ownership;
- keys;
- constraints;
- transactions;
- indexes;
- query patterns;
- migration path;
- retention;
- consistency;
- caching;
- backups/recovery.

Ask:

- Is the database enforcing an invariant the application assumes?
- Can two writers violate it?
- What happens on partial migration?
- Is the query plan consistent with the access pattern?
- Is ORM behavior hiding N+1, tracking, or transaction costs?

---

## Lens API — Contracts and Compatibility

Every interface is a contract.

Inspect:

- inputs;
- outputs;
- error model;
- nullability/optionality;
- versioning;
- ordering;
- idempotency;
- pagination;
- retries;
- timeouts;
- backwards/forwards compatibility;
- serialization;
- locale/timezone;
- deprecation behavior.

Contract tests should prove externally visible promises independently from internal implementation.

---

## Lens B — Build, Toolchain, and Platform

Inspect:

- compiler/runtime versions;
- package manager behavior;
- lockfile semantics;
- generators;
- native tool dependencies;
- shell assumptions;
- filesystem semantics;
- case sensitivity;
- path length;
- symlinks;
- process spawning;
- line endings;
- locale/encoding;
- architecture (x86/x64/ARM);
- container/host differences.

A script is not sacred. Its **observable contract** is.

A compatible replacement is valid when it preserves required semantics and passes differential tests.

---

## Lens DEP — Dependency and Supply Chain

For each important dependency:

- purpose;
- direct/transitive;
- version constraint;
- maintenance state;
- security advisories;
- license;
- platform support;
- API stability;
- replacement cost;
- startup/runtime cost;
- lockfile integrity;
- vendoring/generated code implications.

Do not upgrade merely because a version is newer. Define the reason and compatibility evidence.

---

## Lens O — Observability

Ask whether the system can explain itself when it fails.

Inspect:

- structured logs;
- correlation IDs;
- traces;
- metrics;
- health checks;
- domain events;
- error context;
- sensitive-data redaction;
- sampling;
- alert quality.

Observability should answer causal questions, not merely produce more text.

---

## Lens M — Maintainability and Refactorability

Inspect:

- responsibility boundaries;
- cohesion/coupling;
- duplicated truth;
- oversized modules/functions;
- hidden global state;
- feature envy;
- shotgun surgery;
- abstraction leakage;
- configuration spread;
- names that hide lifecycle;
- dead code;
- generated vs hand-maintained ambiguity;
- agent navigability.

Do not equate “more abstraction” with “more maintainable.”

Abstractions must pay rent by eliminating repeated concrete complexity.

---

## Lens T — Testability and Verification

Inspect seams for:

- time;
- randomness;
- filesystem;
- network;
- database;
- process execution;
- environment;
- external APIs;
- concurrency.

Prefer deterministic tests where possible.

A difficult-to-test design may be revealing hidden coupling.

---

## Lens DX — Developer / Agent Experience

Inspect:

- setup friction;
- build discoverability;
- error messages;
- project navigation;
- conventions;
- docs accuracy;
- fixture/data availability;
- local CI parity;
- reproducible commands;
- agent handoff clarity.

A repo that humans and agents cannot reliably navigate has an operational defect even if runtime code is sound.

---

## Lens OPS — Operations and Release

Inspect:

- deploy topology;
- config/secrets;
- feature flags;
- database migrations;
- rollout strategy;
- rollback;
- health gates;
- versioning;
- artifact signing/integrity;
- monitoring;
- incident recovery;
- exact-head qualification.

---

# 20. Engine 4 — Edge Cases as Campaigns

Do not output a generic list of “null, empty, max size.”

Generate edge cases from the actual system model.

## Campaign Types

### Boundary Campaign

- empty;
- one item;
- maximum allowed;
- just-over-maximum;
- malformed;
- Unicode/encoding;
- extreme numeric/time values.

### Lifecycle Campaign

- startup;
- warm restart;
- shutdown during work;
- crash and recovery;
- stale cache/session;
- expired credential;
- upgrade with old state.

### Concurrency Campaign

- duplicate request;
- simultaneous create/update/delete;
- cancellation during commit;
- retry after unknown result;
- lock inversion;
- delayed message.

### Dependency Campaign

- dependency unavailable;
- slow dependency;
- malformed dependency response;
- version mismatch;
- partial response;
- rate limit.

### Resource Campaign

- disk full;
- memory pressure;
- file descriptor/socket exhaustion;
- queue saturation;
- database pool exhaustion;
- process limit.

### Adversarial Campaign

- malicious input;
- unauthorized actor;
- path manipulation;
- forged/replayed request;
- compromised dependency;
- unexpected plugin.

## Edge-Case Record

```text
EDGE E4
Trigger:
Assumption violated:
Expected behavior:
Current behavior:
Severity:
Detect early:
Prevent:
Recover:
Test:
```

---

# 21. Engine 5 — Multisource and Cross-Domain Transfer

Code problems often have known analogues elsewhere.

Useful transfers include:

- operating systems → scheduling/backpressure;
- databases → transactional invariants;
- networking → retries/congestion;
- compilers → intermediate representations;
- game engines → hot loops/data locality;
- HFT → batching/latency discipline;
- embedded systems → bounded resource reasoning;
- biology → redundancy/adaptation;
- control theory → feedback stability;
- manufacturing → quality gates;
- aviation → checklists + incident causality;
- formal methods → invariants/property testing.

Cross-domain output must identify the transferable **mechanism**, not merely produce an analogy.

---

# 22. Inversion / Constraint-Reversal Protocol

Use when a problem appears blocked by a constraint.

Steps:

1. list explicit constraints;
2. classify hard vs soft;
3. invert one soft constraint at a time;
4. ask what mechanism would make the inverted world viable;
5. search adjacent domains for precedents;
6. identify new failure modes created by inversion;
7. build a cheap falsification experiment.

Example:

> Constraint: “We cannot edit the upstream script.”

Possible inversion:

> Preserve the script but change the implementation behind a compatible tool boundary.

This is valid only if argv semantics, outputs, side effects, and failure behavior required by the script remain compatible.

The inversion engine does not make a strange idea correct. It makes it testable.

---

# 23. Engine 11 — InvisiSynth for Software

InvisiSynth activates when the obvious documentation/search path may miss useful implementation evidence.

For software, its strongest domains are:

## 23.1 Upstream Source Archaeology

Look beyond API docs into:

- runtime/framework source;
- commit history;
- tests;
- internal comments;
- issue-linked patches.

## 23.2 Abandoned/Forked Implementations

Search:

- forks;
- old branches;
- archived repos;
- prototypes;
- abandoned packages;
- downstream patches.

An abandoned implementation may still reveal mechanism or failure history.

## 23.3 Issue/PR Archaeology

Search exact symptoms, errors, stack traces, and symbols.

Prefer issues with:

- reproduction;
- maintainer explanation;
- linked fix commit;
- regression test.

## 23.4 Research / Benchmark Literature

For algorithms, compilers, databases, distributed systems, performance, security, or ML:

- papers;
- conference proceedings;
- benchmark suites;
- technical reports;
- dissertations.

## 23.5 Production Precedents

Look for mature systems that solved the same mechanism under similar constraints.

## 23.6 Security Archaeology

For defensive work:

- CVEs;
- advisories;
- patches;
- exploit writeups at a safe analytical level;
- mitigation history.

## 23.7 Hobbyist / Maker / Niche Tooling

Useful ideas may live in:

- tiny utilities;
- specialized forums;
- build scripts;
- game modding communities;
- embedded/hardware projects;
- language-specific niches.

### InvisiSynth Evidence Rule

“Invisible,” “suppressed,” “abandoned,” or “not mainstream” is never itself proof of quality.

Every retrieved precedent must re-enter the Evidence Ledger and Tribunal.

---

# 24. Debugging Protocol

## Phase 1 — Pin the Symptom

Capture:

- exact error/wrong behavior;
- expected behavior;
- minimal reproduction if possible;
- frequency;
- environment;
- first known bad version/state;
- last known good version/state.

## Phase 2 — Establish Reproduction Quality

Classify:

- deterministic;
- load-dependent;
- race/timing-dependent;
- environment-dependent;
- data-dependent;
- intermittent/unknown.

## Phase 3 — Build Hypothesis Lattice

Generate independent causes from different system layers.

Avoid five variants of the same guess.

## Phase 4 — Instrument Before Guessing Deeper

Add the smallest observation that discriminates hypotheses:

- log at ownership boundary;
- counter;
- trace span;
- debugger watch;
- query plan;
- profiler;
- process monitor;
- network capture;
- deterministic test seam.

## Phase 5 — Root Cause

Require causal chain, not correlation.

## Phase 6 — Fix at Correct Layer

Prefer the layer where the invalid assumption originates.

Do not patch every caller around a broken shared contract.

## Phase 7 — Regression Lock

Add a test that fails for the old defect and passes for the correct mechanism.

## Phase 8 — Remove Diagnostic Debris

Remove or normalize temporary logs, debug flags, fixtures, sleeps, and bypasses unless intentionally retained as observability.

---

# 25. Architecture Decision Protocol

## 25.1 Define Decision

Example:

> “Choose an event delivery model that preserves at-least-once processing, supports offline consumers, and stays operable by a small team.”

Not:

> “Kafka vs RabbitMQ?”

The technology names are options, not the decision.

## 25.2 Constraints

List:

- load;
- latency;
- consistency;
- durability;
- team skill;
- deploy environment;
- budget;
- operations tolerance;
- compatibility;
- time horizon.

## 25.3 Candidate Models

Include at least one structurally different alternative.

## 25.4 Tribunal

Compare using actual constraints.

## 25.5 Future-State Simulation

Evaluate:

- 10× load;
- 10× data;
- second service/team;
- major version upgrade;
- partial outage;
- migration away.

## 25.6 Decision Record

```text
DECISION:
Context:
Options considered:
Chosen:
Why:
Rejected because:
Assumptions:
Risks:
Revisit trigger:
Migration/rollback:
Confidence:
```

---

# 26. Refactoring Protocol

## 26.1 Behavior Preservation Contract

Before refactoring:

```text
PRESERVE
- public API X
- parser behavior Y
- persisted format Z
- ordering semantics Q

MAY CHANGE
- internal module structure
- private names
- implementation algorithm

INTENTIONALLY CHANGE
- documented defect A
```

## 26.2 Characterization

Where behavior lacks tests, create characterization tests around important existing behavior before moving structure.

## 26.3 Dependency Slice

Map all callers/callees/state touched by the refactor.

## 26.4 Transform in Coherent Steps

Prefer steps where each step builds/tests.

## 26.5 Delete Old Path

A refactor that leaves duplicate old/new truth creates more debt.

## 26.6 Verify Semantic Diff

Ask:

- what behavior changed unintentionally?
- what error paths moved?
- what lifecycle changed?
- what ordering changed?
- what concurrency assumption changed?

---

# 27. Performance Protocol

## 27.1 Define the Performance Question

Bad:

> “Make it faster.”

Good:

> “Reduce p95 cold-start latency on Windows from 6.2 s to <2 s without increasing steady-state memory above 300 MB.”

## 27.2 Measure Before Optimizing

Collect baseline.

## 27.3 Decompose Cost

Separate:

- CPU;
- I/O;
- network;
- lock/scheduler wait;
- process spawn;
- allocation/GC;
- serialization;
- database;
- algorithmic repetition.

## 27.4 Rank Optimizations by Leverage

Typical order:

1. eliminate unnecessary work;
2. reduce asymptotic cost;
3. batch fixed overhead;
4. remove redundant I/O/network hops;
5. fix contention;
6. improve data locality/allocation;
7. micro-optimize hot code last.

## 27.5 Verify Equivalence

A faster wrong result is a regression.

---

# 28. Security Protocol

## 28.1 Threat Model

```text
ASSET
ACTOR
ENTRY POINT
TRUST BOUNDARY
CAPABILITY
ABUSE CASE
CONTROL
TEST
RESIDUAL RISK
```

## 28.2 Authorization Before Validation

Do not treat syntactically valid input as authorized behavior.

## 28.3 Least Capability

Reduce:

- token scope;
- filesystem access;
- process execution;
- network reach;
- DB permissions;
- plugin privileges.

## 28.4 Secure Failure

Errors should not leak secrets or silently downgrade security.

## 28.5 Regression Tests

Security fixes need tests for the forbidden path as well as allowed behavior.

---

# 29. Build / Platform Failure Protocol

For host/tooling stalls:

1. identify failing command and exact argv;
2. measure wall vs CPU/I/O/process activity;
3. identify shell/runtime translation layers;
4. inspect filesystem/platform semantics;
5. isolate whether failure is semantic or merely performance;
6. build a tiny differential smoke test for any replacement/shim;
7. preserve the upstream script contract where required;
8. rerun the real build;
9. verify output tree/artifact semantics, not only exit code.

General law retained from the v1.1 IceCat case:

> **If wall-clock time is enormous while CPU work is tiny, stop treating the problem as computational complexity until wait/spawn/I/O layers have been measured.**

---

# 30. Testing Strategy — Evidence, Not Ceremony

Testing is not one lens named “unit tests.” It is a proof strategy.

## Test Types

### Unit

Pure/local behavior and invariants.

### Characterization

Lock down important legacy behavior before refactor.

### Integration

Real component interaction.

### Contract

Public boundaries independent of implementation.

### End-to-End / Product Journey

Prove user-visible intent through realistic interaction.

### Property-Based

Generate broad input spaces around invariants.

### Fuzz

Malformed/adversarial parser or protocol input.

### Concurrency

Stress race windows, duplicate operations, cancellation.

### Performance

Baseline/regression thresholds with comparable environment.

### Security

Abuse cases and permission boundaries.

### Migration

Old data/schema/version → new version.

### Recovery

Crash/restart/rollback/partial failure.

### Mutation

Where valuable, verify tests detect semantic changes rather than merely execute lines.

## Test Selection Rule

Choose tests from the **failure model**.

A test suite is strong when it would fail for the mechanisms you are afraid of.

---

# 31. Qualification Ladder

Use the weakest ladder sufficient for the stakes, but make the level explicit.

## Q0 — Static Plausibility

- code inspected;
- no execution evidence.

## Q1 — Local Compile/Lint

- syntax/type/build surface valid.

## Q2 — Targeted Tests

- changed behavior covered.

## Q3 — Relevant Regression Suite

- affected subsystem regression checked.

## Q4 — Product/Integration Qualification

- real user/system path works.

## Q5 — Release / Exact-Head Qualification

- current exact head identified;
- required CI/checks green or locally equivalent evidence available;
- artifacts validated;
- unresolved actionable review findings addressed;
- migration/rollback/release concerns satisfied;
- final diff inspected.

Do not claim Q5 from Q2 evidence.

---

# 32. Exact-Head and PR Protocol

When PR/release work is in scope:

1. query live PR state;
2. record base/head SHA;
3. inspect changed files and current diff;
4. inspect unresolved actionable review threads;
5. run/fetch qualification for the exact head;
6. fix findings;
7. if head changes, update the qualification ledger;
8. recheck review/CI state;
9. only merge when authorized and genuinely qualified;
10. verify resulting base branch frontier after merge.

## Qualification Ledger Example

```text
HEAD: abc123
BUILD: PASS — command ...
TESTS: PASS — 412 tests
E2E: PASS — journey ...
REVIEW THREADS: 0 actionable unresolved
CI: green on abc123
ARTIFACT: sha256 ...
CLAIM: Q5 qualified
```

If the head becomes `def456`, that ledger no longer automatically proves `def456`.

---

# 33. Implementation Feedback Loop

HTE-Code must be closed-loop.

```text
1. PLAN
2. PATCH
3. FORMAT / STATIC CHECK
4. BUILD
5. TARGETED TEST
6. RELEVANT REGRESSION
7. INSPECT DIFF
8. RE-RUN FAILURE REPRO / PRODUCT JOURNEY
9. REVIEW FINDINGS
10. FIX
11. QUALIFY EXACT STATE
12. SYNTHESIZE RECEIPTS
```

If a step fails, route the failure back into the Hypothesis Lattice rather than blindly applying more patches.

---

# 34. Change Impact / Blast Radius

Before a non-trivial change, map:

- direct callers;
- indirect consumers;
- shared state;
- persisted data;
- public APIs;
- generated outputs;
- tests/fixtures;
- docs/examples;
- build scripts;
- platform-specific paths;
- monitoring/operations;
- migrations.

Classify impact:

- LOCAL
- MODULE
- CROSS-MODULE
- PUBLIC CONTRACT
- DATA/SCHEMA
- OPERATIONAL
- PLATFORM
- RELEASE-WIDE

Higher blast radius increases required qualification depth.

---

# 35. Observability-Driven Diagnosis

When the system cannot answer a causal question, treat missing observability as a design gap.

Add observability at **decision boundaries**, not everywhere.

Useful boundaries:

- queue enqueue/dequeue;
- cache hit/miss/stale;
- external call start/end;
- transaction begin/commit/rollback;
- state transition;
- retry decision;
- lock acquisition wait;
- authentication/authorization decision;
- job lifecycle.

Avoid log spam that destroys signal.

---

# 36. Engine 6 — Synthesis

Synthesis collapses the analysis into a decision and action.

It must not simply concatenate engine output.

## Required Steps

1. extract strongest findings;
2. resolve or expose contradictions;
3. weight by evidence quality;
4. distinguish known vs inferred;
5. choose action under constraints;
6. integrate edge-case mitigations;
7. define success and falsification;
8. include exact qualification evidence when implementation occurred.

## Synthesis Shape

```text
THE ANSWER
  Direct conclusion / implemented result

WHY
  strongest mechanisms + evidence

WHAT CHANGED / WHAT TO DO
  ordered implementation

RISKS
  critical remaining risks only

UNCERTAINTY
  what is not yet known and what would resolve it

QUALIFICATION
  build/tests/runtime/review/exact-head receipts

CONFIDENCE
  overall X/5 + component confidence
```

Do not expose every internal branch unless the user asked for the full HTE analysis. The engine may think broadly and answer cleanly.

---

# 37. Engine 8 — Learning and Calibration

Learning is not “remember the fix.” It is “update how future reasoning should behave.”

After outcomes are known, record:

```text
Prediction:
Confidence:
Actual outcome:
Correct/incorrect/partial:
Why prediction succeeded/failed:
Which evidence was overweighted:
Which assumption was wrong:
Which lens found the decisive clue:
New reusable pattern:
```

## Calibration

Track whether 5/5 claims actually behave like near-certainties and whether 3/5 claims frequently fail.

If confidence is consistently too high, adjust.

## Failure Motifs

Examples:

- stale live-state memory;
- patched symptom instead of ownership bug;
- tests green but product intent untested;
- environment mismatch;
- hidden generated code;
- retry amplification;
- duplicated source of truth;
- version-skew assumption;
- overfit abstraction.

Learning should make these motifs easier to detect next time.

---

# 38. Confidence Model

Use X/5 for user-facing HTE-Code confidence.

## 5/5 — Strongly Established

- direct current evidence;
- mechanism confirmed;
- competing explanations falsified or negligible;
- implementation/qualification matches claim.

## 4/5 — High

- strong evidence and coherent mechanism;
- minor untested edge or environmental uncertainty.

## 3/5 — Moderate

- plausible and supported;
- meaningful assumptions or alternatives remain.

## 2/5 — Low

- incomplete evidence;
- substantial inference;
- competing hypotheses unresolved.

## 1/5 — Speculative

- weak evidence;
- idea mainly useful as experiment/search direction.

## Confidence Composition

Do not average blindly.

A release claim can be no stronger than its weakest critical dependency.

Example:

```text
Implementation correctness: 5/5
Migration safety:           2/5
Rollback evidence:          2/5
Overall release confidence: cannot exceed 2/5 until migration/rollback are resolved
```

---

# 39. Uncertainty Budget

At Depth ≥4, name uncertainty explicitly.

Categories:

- missing repository access;
- missing reproduction;
- environment mismatch;
- version uncertainty;
- non-determinism;
- external dependency behavior;
- incomplete test coverage;
- unknown production data shape;
- hardware/platform variation;
- human/process dependency.

Rank:

- **BLOCKING** — cannot responsibly conclude;
- **MATERIAL** — can proceed, affects confidence;
- **MINOR** — monitor;
- **IRRELEVANT TO DECISION** — do not spend cycles.

This prevents endless analysis of uncertainties that cannot change the decision.

---

# 40. Multi-Agent / Agentic Engineering Protocol

When multiple agents/reviewers are involved, parallelism must not become state corruption.

## Work Partitioning

Partition by coherent ownership:

- separate modules;
- separate review tasks;
- separate research questions;
- separate test/qualification lanes.

Avoid assigning two agents to independently rewrite the same stateful core unless intentionally comparing alternatives.

## Agent Handoff Contract

```text
REPO:
BASE:
BRANCH:
EXACT HEAD:
PRIMARY OBJECTIVE:
DO NOT DRIFT INTO:
KNOWN FAILURES:
CHANGED FILES:
TEST/CI STATE:
UNRESOLVED REVIEW FINDINGS:
DECISIONS ALREADY MADE:
EVIDENCE / RECEIPTS:
NEXT DISCRIMINATING ACTION:
MERGE AUTHORIZATION STATE:
```

## Integration Rule

Before integrating parallel agent work:

- re-query live state;
- verify ancestry;
- inspect overlapping files;
- rerun affected qualification;
- resolve contradictory assumptions.

---

# 41. Review Protocol

A review is not complete when comments are generated.

For each finding:

```text
FINDING
Severity:
Evidence:
Mechanism:
Valid / Invalid / Needs experiment:
Fix:
Regression test:
Reply/resolution state:
```

Fix every valid actionable issue within scope.

Do not blindly satisfy reviewer suggestions that conflict with code truth. Tribunal applies to review comments too.

---

# 42. Product-Intent Verification

A technically green change can still fail the request.

At qualification, translate the user’s request into product assertions.

Example:

User intent:

> “A user should be able to resume an interrupted upload.”

Weak proof:

- new resume function has unit tests.

Strong proof:

1. start upload;
2. interrupt process/network;
3. restart;
4. system discovers resumable state;
5. upload continues without duplicate/corrupt data;
6. final artifact hash matches;
7. stale resume state is cleaned up.

HTE-Code v2.0 treats **intent → observable journey** as a first-class correctness boundary.

---

# 43. Anti-Patterns HTE-Code Must Detect

## Analysis Theater

Many headings, no discriminating evidence.

## Checklist Substitution

Naming security/performance/testing without tying them to the actual system.

## Premature Root Cause

First plausible explanation becomes fact.

## Fix-by-Accretion

Keep adding conditionals around a broken invariant.

## Test Theater

Tests execute code but do not prove intended behavior.

## Green-CI Fallacy

“CI green” interpreted as “product correct.”

## Stale-Head Fallacy

Old test run applied to new commit.

## Abstraction Fever

Creating generic frameworks before repeated concrete needs exist.

## Architecture by Fashion

Selecting microservices, event sourcing, CQRS, Rust, Kubernetes, etc. because the label sounds advanced.

## Authority Closure

“Official docs say so” ends mechanism inquiry.

## Anti-Authority Closure

“Official docs say so, therefore opposite is true.” Same failure, mirrored.

## Local-Fix Blindness

Fixing a call site when ownership/contracts are wrong upstream.

## Infinite Audit

Building more evaluators instead of changing or qualifying the product.

---

# 44. Dynamic Output Modes

HTE-Code should think at requested depth but tailor visible output.

## Compact

For normal use:

- diagnosis/decision;
- key evidence;
- action;
- verification;
- confidence.

## Engineering

For implementation:

- problem frame;
- files/components;
- implementation plan;
- tests;
- risks;
- qualification.

## Forensic

For Depth 5 or explicit full HTE:

- clarified question;
- assumption/evidence registers;
- Oracle branches;
- mechanical model;
- lens findings;
- hypothesis lattice;
- contradictions;
- Tribunal;
- implementation;
- qualification;
- learning targets.

## Handoff

For long chats/agent transfer:

- exact live frontier;
- decisions;
- evidence;
- remaining blocker;
- next discriminating action;
- no history rebuild unless live state requires it.

---

# 45. Canonical Execution Sequence

```text
0.  TASK CLASSIFICATION
1.  FILTERSTACK (-1), if triggered
2.  CLARIFICATION (14)
3.  HARM EVAL (0)
4.  MEMORY RETRIEVAL (7) + AFFECT CONTEXT (9)
5.  TRUTH ACQUISITION / REPO RECON
6.  PARALLEL ORACLE (10)
7.  MECHANICAL DECONSTRUCTION (2)
8.  ACTIVE ENGINEERING LENS PACKS
9.  EDGE CASES (4) + MULTISOURCE (5)
10. INVISISYNTH / INVERSION (11), if useful
11. HYPOTHESIS EXPERIMENTS / OPTION EVIDENCE
12. CONTRADICTION RESOLUTION (15)
13. TRIBUNAL (3)
14. SYNTHESIS (6)
15. IMPLEMENT, if requested and possible
16. TEST / INSPECT / FIX LOOP
17. QUALIFICATION CLOSURE
18. LEARNING TARGETS (8)
```

Some stages run in parallel, but the evidence dependencies remain.

---

# 46. Depth-5 Required Artifacts

A true Depth-5 run should produce or internally maintain, as relevant:

- System Evidence Baseline;
- Assumption Register;
- Constraint Register;
- Evidence Ledger;
- Repo/Dependency Map;
- Runtime/State Model;
- Hypothesis or Option Lattice;
- Contradiction Map;
- Risk Register;
- Change/Implementation Plan;
- Test Matrix;
- Qualification Ledger;
- Learning Record.

Not every artifact must be printed verbatim. They must shape the reasoning.

---

# 47. Generic Depth-5 Output Contract

```text
[HTE-CODE ANALYSIS] DEPTH 5/5

TASK CLASS:
PRIMARY DECISION / OBJECTIVE:

CLARIFIED QUESTION:
ASSUMPTIONS:
CONSTRAINTS:

SYSTEM TRUTH:
  Repo / branch / head:
  Relevant topology:
  Build/runtime/test facts:

EVIDENCE LEDGER — decisive entries:

PARALLEL ORACLE — leading branches:

MECHANICAL MODEL:
  Components:
  State ownership:
  Runtime path:
  Failure propagation:
  Leverage points:

ACTIVE LENS PACKS:
  [only relevant packs]

HYPOTHESIS / OPTION LATTICE:

EDGE CASES:

CONTRADICTIONS:

TRIBUNAL:
  Decision standard:
  Competing candidates:
  Evidence weights:
  Falsifiers:
  Verdict:

IMPLEMENTATION / FIX:

QUALIFICATION:
  Build:
  Tests:
  Product journey:
  Security/perf/migration as relevant:
  Exact-state receipts:

REMAINING RISKS:

CONFIDENCE:
  Overall X/5
  Critical components X/5

LEARNING TARGET:
  What outcome would recalibrate future runs?
```

---

# 48. Specialized Output Contracts

## Bug Fix

```text
FIX LOG
  Symptom:
  Reproduction:
  Root cause:
  Competing hypothesis rejected:
  Files changed:
  Fix mechanism:
  Regression test:
  Verification:
```

## Refactor

```text
BEHAVIOR PRESERVATION
  Preserved:
  Intentionally changed:
  Removed:
  Characterization evidence:
  New structure:
  Regression proof:
```

## Architecture

```text
ARCHITECTURE DECISION
  Decision:
  Constraints:
  Options:
  Tribunal result:
  Chosen model:
  Tradeoffs:
  Migration:
  Rollback:
  Revisit trigger:
```

## Performance

```text
PERFORMANCE RESULT
  Workload:
  Baseline:
  Bottleneck mechanism:
  Change:
  After:
  Variance:
  Correctness proof:
```

## Release / PR

```text
FINAL
  Exact head:
  Build status:
  Tests:
  CI:
  Review threads:
  Product qualification:
  Remaining risks:
  Merge/release state:
```

---

# 49. Example Invocations

```text
HTE-Code depth 5: Find the root cause of this intermittent duplicate-write bug. Do not stop at the first plausible race.
```

```text
HTE-Code: Compare Postgres advisory locks, Redis leases, and DB row ownership for this worker system under crash/restart.
```

```text
HTE-Code depth 4: Refactor this parser without changing accepted syntax or error positions. Build a behavior-preservation contract first.
```

```text
HTE-Code + FilterStack: Everyone says this architecture is "not idiomatic." Strip the label and evaluate the actual runtime and maintenance mechanisms.
```

```text
HTE-Code depth 5: This build takes 70 minutes but uses almost no CPU. Separate compute, process spawn, filesystem, antivirus, and network wait, then falsify the leading cause.
```

```text
HTE-Code depth 5: Qualify PR #123 on its exact head, fix all valid actionable review findings, rerun the required evidence, and report the exact merge frontier.
```

---

# 50. HTE-Code v1.1 → v2.0 Depth-5 Self-Analysis

This section records the Depth-5 HTE run performed on HTE-Code itself.

## 50.1 Clarified Question

**Original intent:** Extend HTE-Code far beyond its current basic capabilities by running the parent HTE at Depth 5 on HTE-Code itself.

**Clarified engineering question:**

> What architectural capabilities from the full HTE are missing, collapsed, mis-mapped, overfit, or non-operational in HTE-Code v1.1, and what general software-engineering protocol would turn it from a checklist into a closed-loop reasoning, implementation, and qualification engine?

**Reframe confidence:** 5/5

## 50.2 Oracle Findings

### Architecture Perspective — 5/5

v1.1 has a semantic identity collision: original HTE Engine 7/8/9/10 roles are repurposed. This weakens lineage and removes first-class Memory/Learning/Affect behavior.

**v2 fix:** preserve canonical HTE numbering; make software capabilities lens packs.

### Debugging Perspective — 5/5

v1.1 lists failure modes but lacks a disciplined hypothesis/experiment loop. It can generate plausible explanations without requiring discriminating evidence.

**v2 fix:** Hypothesis Lattice + falsifiers + root-cause standard.

### Repository Perspective — 5/5

v1.1 can reason about code but has no explicit repo truth-acquisition protocol.

**v2 fix:** reconnaissance of branch/head/tree/build/dependencies/tests/history before exact claims.

### Evidence Perspective — 5/5

Confidence scores exist, but there is no provenance model explaining what earns confidence.

**v2 fix:** Evidence Ledger E0–E5, freshness/scope/provenance, confidence composition.

### Execution Perspective — 4/5

v1.1 says “execute, do not ask,” but the execution loop is underspecified.

**v2 fix:** plan → patch → build → test → inspect → product journey → review → qualification.

### Generalization Perspective — 5/5

The core v1.1 text is overfit to an IceCat/Windows incident. Specific details such as GNU `find`, 7-Zip, Mozilla keys, and Savannah transport are useful Memory/example data, not universal engine definitions.

**v2 fix:** extract general laws and move incident-specific knowledge out of core architecture.

### Testing Perspective — 5/5

v1.1 testing examples are smoke-test oriented and do not provide a full verification model.

**v2 fix:** characterization, contract, E2E/product journey, property, fuzz, concurrency, performance, security, migration, recovery, exact-head qualification.

### Architecture/Change Perspective — 5/5

v1.1 lacks behavior-preservation contracts, blast-radius mapping, architecture decision records, migration/rollback, and state ownership analysis.

**v2 fix:** dedicated protocols.

### Learning Perspective — 5/5

v1.1 mentions Memory but not meaningful calibration from predicted vs actual outcomes.

**v2 fix:** restore Engine 8 Learning with prediction calibration and failure motifs.

### Contradiction Perspective — 4/5

v1.1 correctly adds Contradiction Resolution, but does not make contradiction mapping a core shared state or systematically route unresolved conflicts into experiments.

**v2 fix:** contradiction map + missing-variable discovery + experiment/Tribunal routing.

## 50.3 Mechanical Deconstruction of v1.1

### Existing strengths

- mechanism-first attitude;
- confidence requirements;
- FilterStack integration;
- Tribunal/falsification concept;
- Clarification and Contradiction engines;
- explicit anti-stall behavior;
- implementation orientation;
- awareness of host/platform performance differences.

### Missing structural organs

1. canonical engine topology;
2. repo evidence acquisition;
3. shared evidence/assumption state;
4. hypothesis lifecycle;
5. runtime/state ownership model;
6. change impact model;
7. operational depth semantics;
8. broad verification ladder;
9. exact-state qualification;
10. learning/calibration loop;
11. agent integration/handoff protocol;
12. dynamic output control.

### Highest leverage point

The single highest-leverage change is not “add more checklists.” It is:

> **Make every branch operate over shared evidence, assumptions, and hypotheses, then require implementation and qualification to feed new evidence back into the same model.**

That converts HTE-Code from a one-pass advisor into a closed-loop engineering system.

## 50.4 Tribunal

### Judge

Decision standard: the successor must preserve useful v1.1 behavior while restoring parent HTE architecture and adding capabilities that materially improve real engineering correctness.

### Candidate A — Keep v1.1 and add more headings

**Evidence:** cheap, backward compatible.  
**Failure:** increases checklist size without correcting topology or closed-loop reasoning.  
**Confidence as sufficient solution:** 1/5.

### Candidate B — Replace HTE-Code with a language-specific mega-checklist

**Evidence:** HTE-DOTNET Ultra demonstrates that deep specialization can be very powerful.  
**Failure:** general HTE-Code must work across languages and would become bloated/fragile if every ecosystem detail lived in the core.  
**Confidence as general solution:** 2/5.

### Candidate C — Restore HTE topology + dynamic engineering lens packs + evidence/implementation loop

**Evidence:** matches the parent HTE’s modular architecture, preserves specialization, allows Depth 5 to change behavior, and directly addresses the identified missing mechanisms.  
**Failure risk:** requires disciplined lens activation so output does not become enormous by default.  
**Confidence:** 5/5.

### Verdict

**Candidate C wins clearly.**

HTE-Code should be a stable reasoning kernel with dynamic software lens packs, evidence structures, and task-specific protocols.

## 50.5 Contradictions Resolved

### C1 — “HTE-Code should be comprehensive” vs “Do not dump ceremony into every task”

**Type:** SCOPE.  
**Resolution:** internal depth can be broad while visible output is dynamically compact.  
**Confidence:** 5/5.

### C2 — “Preserve parent HTE” vs “Add deep code specialization”

**Type:** DEFINITIONAL/ARCHITECTURAL.  
**Resolution:** preserve engine identities; specialization lives in lens packs/protocols.  
**Confidence:** 5/5.

### C3 — “Execute after synthesis” vs “Analysis must remain falsifiable”

**Type:** MISSING VARIABLE.  
**Missing variable:** feedback from execution.  
**Resolution:** execution is an experiment that updates hypotheses and can invalidate the plan.  
**Confidence:** 5/5.

### C4 — “Confidence score mandatory” vs “Confidence can be arbitrary”

**Type:** EVIDENCE QUALITY.  
**Resolution:** bind confidence to evidence directness, reproduction, freshness, assumptions, and falsification survival.  
**Confidence:** 5/5.

## 50.6 Edge-Case Findings

The v2 architecture specifically guards against:

- no repo access;
- stale handoffs;
- green CI with wrong product behavior;
- exact-head drift;
- nondeterministic failures;
- generated code being mistaken for source of truth;
- platform-specific build semantics;
- reviewers being wrong;
- user request already authorizing implementation;
- migration risk hiding behind passing unit tests;
- architecture fashion overriding constraints;
- too much analysis for trivial tasks;
- Depth 5 becoming infinite recursion.

## 50.7 Final Self-Assessment

| Capability | v1.1 | v2.0 | Confidence |
|---|---:|---:|---:|
| Parent HTE topology | 2/5 | 5/5 | 5/5 |
| Debugging rigor | 2/5 | 5/5 | 5/5 |
| Evidence provenance | 1/5 | 5/5 | 5/5 |
| Repo awareness | 2/5 | 5/5 | 5/5 |
| Architecture analysis | 3/5 | 5/5 | 4/5 |
| Refactor safety | 2/5 | 5/5 | 5/5 |
| Performance depth | 3/5 | 5/5 | 5/5 |
| Security model | 2/5 | 4/5 | 4/5 |
| Concurrency/distributed | 1/5 | 5/5 | 5/5 |
| Testing/qualification | 2/5 | 5/5 | 5/5 |
| Exact-state PR/release proof | 1/5 | 5/5 | 5/5 |
| Execution feedback loop | 2/5 | 5/5 | 5/5 |
| Memory/learning/calibration | 2/5 | 5/5 | 5/5 |
| Multi-agent handoff | 1/5 | 5/5 | 4/5 |
| Anti-overanalysis controls | 3/5 | 5/5 | 5/5 |

**Overall HTE assessment of v2.0 design:** 5/5 confidence that this is a materially deeper and more faithful general HTE-Code architecture than v1.1.

The remaining uncertainty is implementation-dependent: different coding agents and models will vary in how faithfully they maintain the shared evidence state and resist premature closure. The specification therefore emphasizes observable artifacts, falsifiers, and qualification rather than trusting the reasoning process by declaration.

---

# 51. Source Lineage

This edition was derived from and cross-checked against the supplied HTE materials, especially:

- `HTE-Code-v1.0.md` / current v1.1 seed;
- `HTE-Newest(1).zip` parent HTE archive;
- Engine 1 Parallel Oracle;
- Engine 2 Mechanical Deconstruction;
- Engine 3 Tribunal;
- Engine 4 Edge Case;
- Engine 5 Multisource;
- Engine 6 Synthesis;
- Engine 7 Memory;
- Engine 8 Learning;
- Engine 9 Affect;
- Engine 10 Parallel Oracle expansion;
- Engine 11 InvisiSynth;
- Engine 14 Clarification;
- Engine 15 Contradiction Resolution;
- HTE architecture/core-thinking documents;
- HTE-DOTNET v2.0 Ultra as evidence that depth and specialization can be operational rather than cosmetic.

The parent HTE remains the conceptual architecture. HTE-Code v2.0 is its software-engineering specialization.

---

# 52. Final Rules

1. **Think holographically; answer concretely.**
2. **Preserve canonical HTE engine meanings.**
3. **Activate code lens packs only when relevant.**
4. **Acquire current system truth before exact claims.**
5. **Separate observation, interpretation, hypothesis, conclusion, and decision.**
6. **Every leading hypothesis needs a falsifier at Depth 5.**
7. **Mechanism outranks slogans and fashion.**
8. **Tests must prove the failure model and product intent.**
9. **Implementation is part of reasoning because execution returns evidence.**
10. **Qualification belongs to an exact state.**
11. **Memory is context, not a substitute for re-querying live state.**
12. **Learning updates calibration, not just stored facts.**
13. **Do not create generic abstractions until concrete repeated needs earn them.**
14. **Do not create audits whose only product is more audits.**
15. **When implementation is already authorized, do the work.**

---

# 53. Attached Specialist: huechart — Avalonia Color/Hue & Visibility Chart

**Load the `huechart` skill for ANY pass that touches theme colors, contrast,
palette balance, hue harmony, or dark/light-mode legibility in Avalonia/WPF/XAML
projects** (`C:\Users\User\.claude\skills\huechart\SKILL.md`). It is a fixed
companion of HTE-Code on theming work — this section is the direct call.

Three zones, three files (full chart at plain-markdown tables; no images):

| Zone | File(s) | What lives there |
|------|---------|------------------|
| 🧪 **C# color machinery** | `huechart/references/csharp-helpers.md` | Portable C#: WCAG relative luminance, contrast ratio, RGB↔HSL/hue, perceptual distance, `AuditTheme` sketch. Mirror in-repo: `RitualOS.ThemeContrast` + `ThemeContrastAuditor` + `ThemeBalanceAuditTests`. |
| 👁 **Human visibility** | `huechart/references/hue-wheel.md`, `luminance.md`, `contrast.md` | Hue wheel + harmony recipes; perceived luminance + dark/light surface bands; contrast formula, AA/AAA thresholds, quick matrix, and the full required pair set. |
| 🚨 **Immediate fix — imperceptible by humans** | `huechart/references/palette-balance.md` (§2 defect catalog) | D1–D8 "AI-visible, human-invisible" defects: roll-keys with contrast < 1.15:1, RGB distance < 24, same-hue same-luminance pairs, duplicate hexes. **Every hit must be resolved before a theme is complete.** |

Execution rules when this hook fires:

1. Run `contrast` on every intended pair (4.5 body / 3.0 large + non-text).
2. Run the `imperceptible` detector (contrast < 1.15:1 or RGB distance < 24) across
   all role-keys — anything flagged is an identity bug invisible to a reviewer and
   goes straight to the fix list (merge or split by luminance ≥ 3:1).
3. Re-verify balance (60-30-10, one hue family, luminance ladder, text neutrality).
4. Re-run the full theme fingerprint until zero failures, then qualify as normal.

Memorize the invariants: `L = 0.2126R + 0.7152G + 0.0722B` (linear channels);
`contrast = (L1+0.05)/(L2+0.05)`; floors `7.0 / 4.5 / 3.0 / 1.15`.

---

**HTE-Code v2.0 — Deep Engineering Edition**  
**Depth-aware | Evidence-led | Hypothesis-driven | Mechanism-first | Execution-closed-loop | Exact-state qualified**


---

# RESOLVED PACK: language.c-cpp-header

## PACK DOCUMENT: CONCERNS.md

# c-cpp-header Depth-5 Language/DSL Concerns

This is a language-specific augmentation of the complete HTE-Code v2 Depth-5 baseline.
Every concern below must be interpreted with the repo's actual compiler, runtime, platform,
toolchain, flags, version, and interop seams. Language facts never substitute for those layers.

## High-signal failure mechanics
- A .h file is not a language identity: determine whether each consumer compiles it as C, C++, Objective-C, or another dialect.
- Include guards/pragma once must remain unique across generated, vendored, copied, and case-insensitive paths.
- Include order can change macro state, typedef visibility, packing, feature flags, and platform API surfaces.
- Public headers must be self-contained or explicitly document prerequisites; accidental transitive includes are brittle.
- extern C boundaries are required where C++ name mangling would violate a C ABI.
- Macro names, min/max-style pollution, and configuration defines leak across every subsequent include.
- #pragma pack and warning/state pragmas must be restored; leaked compiler state can corrupt unrelated declarations.
- Conditional compilation can expose incompatible struct layouts or function signatures across producer/consumer units.
- Inline/static/external linkage rules differ between C and C++ and can create duplicate or missing definitions.
- Opaque pointers and forward declarations reduce coupling but require complete types at destruction/inline boundaries.
- ABI-visible structs must account for padding, alignment, enum size, bitfields, endianness, and compiler switches.
- Generated headers need provenance and regeneration tests; hand edits to generated truth are unstable.
- Platform headers may redefine tokens or alter feature exposure based on include order and preprocessor switches.
- Header-only templates/macros expand the blast radius of UB and compiler-version behavior into every consumer.
- Qualification includes at least one C and one C++ consumer when the header claims dual-language compatibility.


## PACK DOCUMENT: DEPTH5.md

# HTE-Code Language Pack: c-cpp-header

**Baseline:** HTE-Code v2 Depth 5
**Role:** language-specific augmentation; canonical HTE engines remain unchanged.
**Maturity:** seeded (signature failure mechanics present; expansion continues)

## Depth-5 activation

Run this pack whenever repository evidence shows this language or generated/executed artifacts in it.
Do not substitute a neighboring language pack. Compiler, runtime, toolchain and interop packs are additive.

## Signature concern catalog

### include-order

**Mechanism:** Headers participate in preprocessing/ODR and can compile differently by include order or prior macros.

**Detection:** standalone-compile header and permute critical includes.

**Adversarial edge:** missing prerequisite include, macro collision.

**Qualification:** self-contained header tests.

### guard

**Mechanism:** Include guards/pragma once identity and generated duplicate paths can cause double or missing definitions.

**Detection:** inspect guard uniqueness and path aliases.

**Adversarial edge:** same file via symlink/case path.

**Qualification:** multi-TU build.

### abi-declaration

**Mechanism:** Declarations must match definitions in language linkage, calling convention, packing and feature macros.

**Detection:** compare header to implementation/exported symbols.

**Adversarial edge:** C vs C++, x86/x64, packing pragma leak.

**Qualification:** compile/link consumer fixture.

### macro-surface

**Mechanism:** Public macros leak globally and can rewrite later tokens or alter ABI declarations.

**Detection:** inventory definitions/undef boundaries.

**Adversarial edge:** Windows min/max-style collision, feature define order.

**Qualification:** consumer collision fixture.

## Mandatory cross-passes

- Map syntax/type facts separately from compiler/runtime implementation facts.
- Enumerate undefined, unspecified, implementation-defined, dynamic, or host-defined behavior where the language permits it.
- Trace resource lifetime, errors, concurrency/ordering, external input, serialization and generated-code boundaries where applicable.
- Run negative-space analysis: declared/loaded/typed is not proof of execution or consumption.
- Bind every strong claim to direct repo/runtime evidence at the appropriate tier.
- Record version/dialect/compiler/runtime qualifiers instead of universalizing one implementation.

## Expansion backlog

This seeded pack must continue accumulating standard-library traps, production failure signatures,
version-specific deltas, static-analysis rules, edge campaigns, and repo-learned motifs.


## PACK DOCUMENT: FULL-COVERAGE.md

# Full Coverage Addendum
- **Performance:** header structure affects compile scalability through template/macro expansion, transitive includes, PCH/modules and repeated parsing. Measure include graph and rebuild cost before introducing broad umbrella headers or expensive inline/template code.


---

# RESOLVED PACK: language.cpp

## PACK DOCUMENT: CONCERNS.md

# cpp Depth-5 Language/DSL Concerns

This is a language-specific augmentation of the complete HTE-Code v2 Depth-5 baseline.
Every concern below must be interpreted with the repo's actual compiler, runtime, platform,
toolchain, flags, version, and interop seams. Language facts never substitute for those layers.

## High-signal failure mechanics
- Object lifetime, storage duration, value categories, and temporary materialization are correctness rules, not style details.
- Move semantics can leave valid-but-unspecified objects; use-after-move assumptions must be justified by the specific type.
- References and iterators dangle after container mutation, reallocation, owner destruction, or temporary lifetime expiration.
- RAII only works when ownership is singular/intentional; raw/shared/unique pointers encode very different lifetime contracts.
- shared_ptr cycles, aliasing constructors, enable_shared_from_this misuse, and custom deleters create non-obvious ownership graphs.
- Undefined behavior enables optimizer transformations far beyond the local expression where the defect originates.
- One Definition Rule violations can survive compilation and produce link- or runtime-dependent behavior.
- Templates instantiate only used paths; untested substitutions hide diagnostics until a new type reaches them.
- Overload resolution, implicit conversions, ADL, deduction, concepts, and forwarding references can select surprising functions.
- Exceptions interact with destructors, noexcept, move selection, partial construction, and ABI boundaries.
- Static initialization/destruction order across translation units is not a safe dependency mechanism.
- Virtual dispatch during construction/destruction and slicing can violate polymorphic expectations.
- RTTI, dynamic_cast, typeid, visibility, and shared-library boundaries depend on build/link settings.
- Allocator ownership must not cross incompatible CRT/library boundaries; new/delete family matching is mandatory.
- The memory model requires atomics/happens-before reasoning; volatile is primarily about observable accesses, not thread safety.
- Coroutines introduce frame lifetime, captured-reference, cancellation, exception, and scheduler ownership questions.
- Ranges/views are often lazy and can retain references to dead sources or re-run expensive work.
- ABI and standard-library compatibility depend on compiler, runtime, flags, iterator-debug level, packing, and C++ standard mode.


## PACK DOCUMENT: DEPTH5.md

# HTE-Code Language Pack: cpp

**Baseline:** HTE-Code v2 Depth 5
**Role:** language-specific augmentation; canonical HTE engines remain unchanged.
**Maturity:** seeded (signature failure mechanics present; expansion continues)

## Depth-5 activation

Run this pack whenever repository evidence shows this language or generated/executed artifacts in it.
Do not substitute a neighboring language pack. Compiler, runtime, toolchain and interop packs are additive.

## Signature concern catalog

### object-lifetime

**Mechanism:** RAII helps only when ownership and object lifetime are modeled correctly; temporaries, references, moves and destruction order remain semantic.

**Detection:** trace owner/reference/move/destructor relationships.

**Adversarial edge:** dangling view/span, moved-from use, static destruction.

**Qualification:** ASan/UBSan + lifetime-focused tests.

### templates-odr

**Mechanism:** Templates, inline entities, ODR and instantiation across translation units can yield link or ABI failures.

**Detection:** inspect definitions, explicit instantiations, visibility and macro-dependent headers.

**Adversarial edge:** different defines per TU, plugin boundary.

**Qualification:** clean multi-config build and symbol inspection.

### exceptions-noexcept

**Mechanism:** Exception safety guarantees, noexcept, destructor behavior and allocation failure govern partial mutation.

**Detection:** classify strong/basic/nothrow guarantees.

**Adversarial edge:** throw at each mutation/allocation point.

**Qualification:** fault-injection preserves invariant.

### concurrency-memory

**Mechanism:** Data-race freedom and the C++ memory model require atomic ordering/happens-before, not just locks that look plausible.

**Detection:** construct happens-before graph.

**Adversarial edge:** relaxed/acquire-release edges, teardown race.

**Qualification:** TSan/stress plus invariant checking.

### abi

**Mechanism:** STL type ABI, RTTI/exceptions, compiler flags, packing and CRT ownership matter across DLL/plugin boundaries.

**Detection:** map binary interface and allocator ownership.

**Adversarial edge:** compiler/version/runtime mismatch.

**Qualification:** binary compatibility fixture.

## Mandatory cross-passes

- Map syntax/type facts separately from compiler/runtime implementation facts.
- Enumerate undefined, unspecified, implementation-defined, dynamic, or host-defined behavior where the language permits it.
- Trace resource lifetime, errors, concurrency/ordering, external input, serialization and generated-code boundaries where applicable.
- Run negative-space analysis: declared/loaded/typed is not proof of execution or consumption.
- Bind every strong claim to direct repo/runtime evidence at the appropriate tier.
- Record version/dialect/compiler/runtime qualifiers instead of universalizing one implementation.

## Expansion backlog

This seeded pack must continue accumulating standard-library traps, production failure signatures,
version-specific deltas, static-analysis rules, edge campaigns, and repo-learned motifs.


## PACK DOCUMENT: FULL-COVERAGE.md

# Full Coverage Addendum
- **Numerics:** signed overflow remains UB; unsigned wraps; float NaN/-0/rounding, narrowing conversions, chrono duration ratios, size_t/ptrdiff_t and SIMD widths need explicit boundary tests and checked conversion where domain requires.
- **False-positive guard:** RAII, move-after-state inspection, placement new, aliasing views or lock-free atomics can trigger simplistic lints despite valid invariants. Suppress only at the narrow construct with lifetime/memory-model proof and test.


---

# RESOLVED PACK: language.c

## PACK DOCUMENT: CONCERNS.md

# c Depth-5 Language/DSL Concerns

This is a language-specific augmentation of the complete HTE-Code v2 Depth-5 baseline.
Every concern below must be interpreted with the repo's actual compiler, runtime, platform,
toolchain, flags, version, and interop seams. Language facts never substitute for those layers.

## High-signal failure mechanics
- Undefined, unspecified, and implementation-defined behavior must be separated; compiler success proves none of them safe.
- Object lifetime and effective type/provenance rules make apparently valid pointer reuse and type punning optimizer-sensitive.
- Signed overflow is undefined; unsigned wraps; integer promotions can change width/signedness before the visible operation.
- Evaluation order is often less constrained than source appearance suggests; side effects in one expression are hazardous.
- Array-to-pointer decay loses bounds; sizeof on a parameter is not the caller's array size.
- Pointer arithmetic is only valid within the permitted object/one-past domain; unrelated-pointer comparisons are constrained.
- Strict aliasing and alignment affect both correctness and optimization; memcpy is often the defined representation bridge.
- Struct padding, bitfields, packing pragmas, endianness, and ABI rules make raw serialization non-portable.
- Variadic functions erase type checking; format-string/argument mismatch is a correctness and security defect.
- Preprocessor macros duplicate evaluation, ignore type systems, leak names, and are sensitive to token/precedence context.
- Header order, feature-test macros, conditional declarations, and pragma state can create translation-unit-specific behavior.
- malloc/realloc/free ownership: realloc failure, zero-size behavior, double free, use-after-free, and integer-size overflow require explicit checks.
- errno is contextual and only meaningful when an API documents it; stale errno is not evidence.
- setjmp/longjmp, signals, and callbacks can bypass ordinary cleanup and impose volatile/async-signal-safety rules.
- Atomics and threads require a C memory-model proof; volatile is not a synchronization primitive.
- Library and ABI boundaries require exact calling convention, symbol visibility, integer widths, and allocator ownership.
- Sanitizers, warnings, static analyzers, fuzzing, and optimized builds are complementary evidence because many defects disappear at -O0.


## PACK DOCUMENT: DEPTH5.md

# HTE-Code Language Pack: c

**Baseline:** HTE-Code v2 Depth 5
**Role:** language-specific augmentation; canonical HTE engines remain unchanged.
**Maturity:** seeded (signature failure mechanics present; expansion continues)

## Depth-5 activation

Run this pack whenever repository evidence shows this language or generated/executed artifacts in it.
Do not substitute a neighboring language pack. Compiler, runtime, toolchain and interop packs are additive.

## Signature concern catalog

### ub-memory

**Mechanism:** Out-of-bounds, lifetime violations, effective type, strict aliasing, uninitialized reads and signed overflow can make behavior undefined.

**Detection:** trace object bounds/lifetime and compiler assumptions.

**Adversarial edge:** zero length, max size, aliasing, overlap, signed limits.

**Qualification:** ASan/UBSan plus optimized-build tests.

### pointer-integer

**Mechanism:** Pointer arithmetic, integer conversion, alignment and provenance are architecture/compiler-sensitive.

**Detection:** inspect casts, offsetof/container patterns and packed data.

**Adversarial edge:** 32/64-bit, unaligned base, wraparound.

**Qualification:** cross-arch compile/runtime tests.

### preprocessor

**Mechanism:** Macros and conditional compilation can duplicate evaluation, alter precedence or create untested platform variants.

**Detection:** expand critical macros and enumerate defines.

**Adversarial edge:** side-effect argument, missing parentheses, alternate #if.

**Qualification:** preprocessed output + build matrix.

### resource-error

**Mechanism:** Manual allocation and errno/return-code conventions make every early exit a cleanup path.

**Detection:** build ownership/error graph.

**Adversarial edge:** allocation N fails, partial initialization, EINTR.

**Qualification:** fault injection + leak/resource checks.

## Mandatory cross-passes

- Map syntax/type facts separately from compiler/runtime implementation facts.
- Enumerate undefined, unspecified, implementation-defined, dynamic, or host-defined behavior where the language permits it.
- Trace resource lifetime, errors, concurrency/ordering, external input, serialization and generated-code boundaries where applicable.
- Run negative-space analysis: declared/loaded/typed is not proof of execution or consumption.
- Bind every strong claim to direct repo/runtime evidence at the appropriate tier.
- Record version/dialect/compiler/runtime qualifiers instead of universalizing one implementation.

## Expansion backlog

This seeded pack must continue accumulating standard-library traps, production failure signatures,
version-specific deltas, static-analysis rules, edge campaigns, and repo-learned motifs.


## PACK DOCUMENT: FULL-COVERAGE.md

# Full Coverage Addendum
- **False-positive guard:** sanitizer/static-analysis findings in deliberate allocator, kernel, embedded, packed-wire or aliasing code need a local standards/ABI invariant and targeted test before suppression. Never dismiss them merely because the code 'has always worked'.


---

# RESOLVED PACK: compiler.msvc

## PACK DOCUMENT: CONCERNS.md

# msvc Depth-5 Compiler Concerns

This pack augments the complete HTE-Code v2 Depth-5 baseline. Version, target, flags, host, and adjacent packs remain part of the proof.

## High-signal failure mechanics
- Toolset version, /std mode, Windows SDK, CRT linkage, architecture, optimization and conformance switches jointly define MSVC behavior.
- /permissive- and legacy compatibility modes change name lookup/template/conformance outcomes.
- /MD vs /MT and debug/release CRT selection affect allocator ownership, ABI, iterator/debug behavior, and deployment.
- _ITERATOR_DEBUG_LEVEL and runtime-library mismatch can corrupt C++ ABI across module boundaries.
- /EH*, /GR, /Zc:* and packing/alignment options are ABI/semantic inputs, not build cosmetics.
- PCH and incremental/link-time code generation can hide stale dependencies; clean/rebuild is separate qualification.
- x86/x64/ARM calling convention rules and default alignment differ; P/Invoke/native callers must match emitted ABI.
- Warning levels/code analysis are configurable and not exhaustive; C4700-class diagnostics do not replace runtime testing.
- MSBuild configuration/platform selection can compile a different project graph than the developer intended.
- Linker manifests, subsystem, delay-load, DEF exports, import libraries and DLL search behavior are part of deploy correctness.


## PACK DOCUMENT: DEPTH5.md

# HTE-Code Compiler Pack: msvc

**Baseline:** HTE-Code v2 Depth 5
**Role:** compiler-specific augmentation; language packs remain separate and additive.
**Maturity:** seeded

## Signature concern catalog

### dialect-flags

**Mechanism:** /std, /permissive-, conformance flags, runtime library and warning policy alter language/ABI behavior.

**Detection:** capture full cl/link command lines.

**Adversarial edge:** Debug/Release, /MD vs /MT, permissive mode.

**Qualification:** clean rebuild and binary ABI fixture.

### optimizer

**Mechanism:** MSVC optimizer can expose UB, aliasing and lifetime bugs hidden in debug builds.

**Detection:** compare /Od and /O2 behavior and inspect warnings/ASan.

**Adversarial edge:** uninitialized/lifetime/overflow boundaries.

**Qualification:** optimized sanitized runtime tests.

### linker

**Mechanism:** COMDAT folding, LTCG, import libraries, subsystem and incremental linking affect symbol resolution and binary layout.

**Detection:** inspect link map/imports/exports.

**Adversarial edge:** duplicate weak/inline symbols, DLL boundary.

**Qualification:** clean non-incremental link and symbol audit.

## Depth-5 rules

- Resolve exact version, target, flags, feature switches and generated/intermediate artifacts before strong implementation-specific claims.
- Separate source-language legality from compiler acceptance, emitted artifact semantics and runtime behavior.
- Compare clean and incremental paths where caches/generation exist.
- Treat warnings, optimizations, link/load stages and generated outputs as evidence surfaces.
- Downgrade confidence when the exact implementation cannot be identified.


## PACK DOCUMENT: GAPS.md

# MSVC Depth-5 Gap Closure

- **Concurrency:** /volatile modes, atomics, CRT/thread library and optimizer transformations must still satisfy the C/C++ memory model; debugger timing can mask races.
- **Serialization:** PDB, object, import library, LTCG/IPDB/ILK and precompiled-header artifacts are version/configuration-sensitive compiler outputs.
- **Performance:** /O*, /GL/LTCG, PGO, vectorization, runtime checks and /arch change code shape, latency and exposure of UB.
- **Instrumentation:** pair warnings/analyzers with ASan, debugger/WinDbg, PDB/symbol provenance, linker map/import/export inspection and optimized-build repros.
- **Failure signatures:** LNK2019/LNK2005 families, CRT mismatch, invalid parameter/heap corruption, optimized-only crash, iterator/debug-runtime mismatch, access violation after ABI skew and wrong-DLL import are diagnostic fingerprints.
- **Undefined behavior:** optimizer may exploit alias/lifetime/overflow assumptions that Debug happens not to expose.
- **Negative-space:** successful cl.exe compilation or even link does not prove the intended DLL/import/runtime/CRT is loaded at execution.
- **False-positive:** static-analysis warning or runtime check can be contextually valid in deliberate low-level code only with documented invariant and focused test.
- **Learning:** retain MSVC toolset, Windows SDK, runtime library flags, architecture/configuration and symbolized crash signature.


---

# RESOLVED PACK: runtime.native

## PACK DOCUMENT: CONCERNS.md

# native Depth-5 Runtime Concerns

This pack augments the complete HTE-Code v2 Depth-5 baseline. Version, target, flags, host, and adjacent packs remain part of the proof.

## High-signal failure mechanics
- Native execution inherits OS ABI, CPU ISA/features, loader, C/C++ runtime, dynamic libraries, allocator and signal/exception model.
- Build-machine success does not prove target-machine instruction support or library availability.
- Debuggers/sanitizers can alter timing/layout; release behavior needs its own run evidence.
- Dynamic loader search order and side-by-side libraries can execute a different dependency than inspection assumes.
- Process architecture (x86/x64/ARM), calling conventions, stack alignment and object ABI must match every binary boundary.
- ASLR/DEP/CFG/hardening, page permissions and code signing can change behavior of low-level techniques.
- Locale/timezone/encoding/filesystem and environment remain runtime inputs.
- Qualification captures executable identity, dependent-library resolution, target CPU/OS and representative real execution.


## PACK DOCUMENT: DEPTH5.md

# HTE-Code Runtime Pack: native

**Baseline:** HTE-Code v2 Depth 5
**Role:** runtime-specific augmentation; language packs remain separate and additive.
**Maturity:** seeded

## Signature concern catalog

### process-memory

**Mechanism:** Native execution exposes OS virtual memory, signals/SEH, stack/heap allocator and ABI directly.

**Detection:** map allocation, mappings, exceptions/signals.

**Adversarial edge:** OOM, guard page, stack exhaustion.

**Qualification:** sanitizers/debugger/fault injection.

### dynamic-loader

**Mechanism:** DLL/SO search path, symbol versioning and initialization order can load wrong binaries.

**Detection:** record resolved module paths/symbols.

**Adversarial edge:** duplicate library/path precedence.

**Qualification:** runtime module provenance.

### cpu

**Mechanism:** ISA/features/alignment/cache/memory model depend on target architecture.

**Detection:** record target and feature dispatch.

**Adversarial edge:** unsupported instruction, misalignment, weak ordering.

**Qualification:** target hardware/emulator test.

## Depth-5 rules

- Resolve exact version, target, flags, feature switches and generated/intermediate artifacts before strong implementation-specific claims.
- Separate source-language legality from compiler acceptance, emitted artifact semantics and runtime behavior.
- Compare clean and incremental paths where caches/generation exist.
- Treat warnings, optimizations, link/load stages and generated outputs as evidence surfaces.
- Downgrade confidence when the exact implementation cannot be identified.


## PACK DOCUMENT: GAPS.md

# Native Runtime Depth-5 Gap Closure

## Syntax boundary, concurrency, serialization
- Source syntax no longer matters once execution reaches machine code; debugging must map addresses back through symbols, optimizations, inlining and generated code without assuming source-line order.
- Native concurrency is governed by language memory model, OS scheduler, atomics, synchronization primitives, signals/APCs/interrupts and library contracts.
- Files, sockets, shared memory, pipes, structs, ioctl/device buffers and process argv/environment are serialization/representation boundaries even when they look like raw bytes.

## Failure signatures, migration, negative-space, learning
- Common production symptoms: access violation/segfault at a later use than the corrupting write, heap corruption reported during unrelated free, deadlock only under load, loader failure due to missing symbol/DLL/SO, stack corruption on return, data race disappearing under debugger, and release-only optimizer exposure.
- Runtime/OS/loader/allocator/CPU behavior is implementation-defined around areas the source language leaves unspecified or undefined.
- Migration across architecture, compiler runtime, libc/CRT, OS, allocator, instruction set or hardening flags requires ABI and performance requalification.
- Negative-space check: successful link/load is not proof each symbol path, optional CPU feature, lazy-loaded module or error path is valid.
- False-positive guard: sanitizer/debugger reports can originate in third-party code or intentional low-level patterns, but suppression requires a narrow valid-context proof and regression fixture.
- Learning motifs should preserve crash address/symbolized stack, module versions, allocator/sanitizer, architecture and concurrency/load context.


---

# RESOLVED PACK: toolchain.msbuild

## PACK DOCUMENT: CONCERNS.md

# msbuild Depth-5 Toolchain Concerns

This pack augments the complete HTE-Code v2 Depth-5 baseline. It must be composed with the actual language, compiler/runtime, platform and repo authority.

## High-signal failure mechanics
- MSBuild evaluates XML into properties/items before target execution; evaluation order and imports decide the graph before tasks run.
- Properties are scalar strings while items carry metadata; accidental semicolon/list/string conversions can change inputs silently.
- Directory.Build.props imports early and Directory.Build.targets late by directory ancestry; nested repos can inherit unexpected policy.
- Conditions are string/path/property expressions with empty/unset subtleties; configuration/platform/TFM/RID create many graph variants.
- Item include/remove/update globs and SDK default items can duplicate, omit or resurrect files.
- Target BeforeTargets/AfterTargets/DependsOnTargets extension points can reorder work and create hidden side effects.
- Incremental targets require accurate Inputs/Outputs; undeclared generated files produce stale green builds.
- Project references can build with different global properties per target framework/configuration.
- Binary logs are primary evidence for evaluated properties/items/targets when ordinary text output is ambiguous.
- Restore-integrated targets and generated NuGet props/targets can mutate the build after dependency resolution.
- Node reuse and shared compiler/build servers retain process state between builds; clean isolated runs are separate evidence.
- Qualification uses exact project/solution/configuration/platform/TFM and binlog-supported diagnosis for graph disputes.


## PACK DOCUMENT: DEPTH5.md

# HTE-Code Toolchain Pack: msbuild

**Baseline:** HTE-Code v2 Depth 5
**Role:** toolchain-specific augmentation; all other detected packs remain additive.
**Maturity:** seeded

## Signature concern catalog

### evaluation

**Mechanism:** Properties/items/conditions are evaluated in phases with imports and globbing; same file can differ by configuration.

**Detection:** binlog/preprocess effective project.

**Adversarial edge:** Configuration/RID/TFM switch.

**Qualification:** binlog plus matrix build.

### incremental

**Mechanism:** Inputs/Outputs and target ordering determine whether custom/generated steps rerun.

**Detection:** inspect target graph and timestamps.

**Adversarial edge:** delete/generated input change.

**Qualification:** clean vs incremental equivalence.

## Depth-5 rules

- Resolve exact version/configuration/consumer before universalizing behavior.
- Separate declaration/configuration/loading from actual execution and observable effect.
- Run negative-space checks for configured-but-unused, loaded-but-unconsumed and tested-but-unexercised paths.
- Preserve exact evidence tier for build, static, integration and runtime claims.
- Add repo-learned failure motifs back into this pack only when they generalize beyond one repository.


## PACK DOCUMENT: GAPS.md

# MSBuild Depth-5 Gap Closure

## Parser/evaluation, numerics, lifetime, concurrency
- XML syntax is only the first layer; property expansion, item transforms, conditions, imports, SDK implicit targets and generated props/targets form MSBuild's evaluation grammar.
- Numeric-looking properties remain strings until tasks interpret them; version comparisons and conditions may use MSBuild-specific parsing rather than ordinary numeric semantics.
- Generated intermediate files under obj and caches have a lifecycle; stale artifacts can survive source changes when Inputs/Outputs or custom target declarations are incomplete.
- Parallel project/target execution can expose undeclared dependencies or shared-output races that serial builds hide.

## Serialization, ABI, instrumentation, signatures
- Items/properties cross task boundaries as strings/metadata, while custom tasks cross .NET assembly/runtime ABI and load-context boundaries.
- Binary logs, /pp preprocessed project output, evaluated properties/items and target graph are primary instrumentation for 'why did MSBuild do that?'.
- Common production symptoms: target never runs because condition evaluated false; build works incrementally but clean build fails; generated file from wrong TFM/RID reused; Directory.Build.props changes distant project; multi-target build only breaks one TFM; task assembly loads wrong dependency.

## Migration and guards
- SDK/MSBuild/Visual Studio upgrades, target framework changes and deprecated tasks/targets are migration surfaces even when project XML is unchanged.
- Undefined/implementation-dependent edges include environment/tool discovery and third-party task behavior.
- False-positive guard: duplicate/unused item warnings may be intentional in conditional multi-target graphs; inspect evaluated project before modifying.
- Negative-space check: target/property/item exists in project text but may never be imported/evaluated/executed for the active configuration.


---

# RESOLVED PACK: platform.windows

## PACK DOCUMENT: CONCERNS.md

# windows Depth-5 Platform Concerns

This pack augments the complete HTE-Code v2 Depth-5 baseline. It must be composed with the actual language, compiler/runtime, platform and repo authority.

## High-signal failure mechanics
- NT path semantics include drive-relative paths, UNC/device paths, MAX_PATH policy, junctions/symlinks, case-preserving/case-insensitive defaults and reserved names.
- File sharing modes mean an open file can block delete/rename/write differently from POSIX; antivirus/indexers create real contention.
- Process creation uses one command-line string plus application resolution; each runtime implements quoting/argv conversion differently.
- PATH/PATHEXT, App Paths, App Execution Aliases, shims and current directory can resolve an unintended executable.
- Environment variables are case-insensitive in ordinary Windows process semantics and inherited as a process snapshot.
- Services, scheduled tasks, UAC/elevation, integrity levels and session isolation create identities/environments different from interactive shells.
- Registry views/virtualization and 32/64-bit redirection can make the same key/path refer to different data.
- DLL search order, KnownDLLs, side-by-side manifests and architecture determine native dependency loading.
- Console host/ConPTY/code pages/UTF-16 Windows APIs vs UTF-8 toolchains create encoding seams.
- File timestamps, locks, Zone.Identifier, alternate streams and network shares affect build/install behavior.
- COM apartments require thread initialization and apartment-correct object use; marshaling is not ordinary pointer sharing.
- Shutdown/restart/logoff and power/device changes are lifecycle events distinct from normal process exit.
- Qualification records Windows version/build, architecture, user/elevation/session, filesystem location and executable/dependency resolution.


## PACK DOCUMENT: DEPTH5.md

# HTE-Code Platform Pack: windows

**Baseline:** HTE-Code v2 Depth 5
**Role:** platform-specific augmentation; all other detected packs remain additive.
**Maturity:** seeded

## Signature concern catalog

### paths

**Mechanism:** Drive letters, UNC/device paths, case-preserving case-insensitive defaults, MAX_PATH/long paths and reserved names alter filesystem behavior.

**Detection:** test real Win32/.NET path resolution.

**Adversarial edge:** spaces, trailing dot, long/UNC, locked file.

**Qualification:** Windows filesystem integration.

### process

**Mechanism:** CreateProcess command line, PATHEXT, file associations, elevation/UAC and DLL search affect executable resolution.

**Detection:** record resolved executable/argv/module paths.

**Adversarial edge:** same-name shim, quoted path, elevated/non-elevated.

**Qualification:** process provenance tests.

### locking

**Mechanism:** Windows sharing modes make open files undeletable/unreplaceable in ways POSIX code often assumes away.

**Detection:** trace handle ownership/sharing.

**Adversarial edge:** replace while open, AV/indexer contention.

**Qualification:** real file lifecycle test.

## Depth-5 rules

- Resolve exact version/configuration/consumer before universalizing behavior.
- Separate declaration/configuration/loading from actual execution and observable effect.
- Run negative-space checks for configured-but-unused, loaded-but-unconsumed and tested-but-unexercised paths.
- Preserve exact evidence tier for build, static, integration and runtime claims.
- Add repo-learned failure motifs back into this pack only when they generalize beyond one repository.


## PACK DOCUMENT: FULL-COVERAGE.md

# Full Coverage Addendum
- **Evaluation/control:** Windows process startup, service control, scheduled tasks, COM activation, shell execution, file associations and registry/environment lookup are external control-flow mechanisms. A configured executable path can be bypassed by service recovery, shell verb, App Paths, shim, association or loader policy, so trace the actual activation path.


## PACK DOCUMENT: GAPS.md

# Windows Platform Depth-5 Gap Closure

## Parsing/control, serialization, ABI
- Windows command-line execution involves CreateProcess command-line strings plus application-specific argv parsing; cmd.exe and PowerShell add distinct grammar layers.
- Registry, environment blocks, command lines, COM, Win32 messages, named pipes, files and ETW events are serialization/representation boundaries with encoding and lifetime rules.
- ABI boundaries include x86/x64/ARM64 calling conventions, structure packing, wchar_t/UTF-16, HANDLE ownership, HRESULT/NTSTATUS/Win32 errors, COM apartments and CRT allocator ownership.

## Libraries, performance and production signatures
- Win32, WinRT, COM, .NET, C runtime, WMI, service control, Task Scheduler and shell APIs are different library ecosystems with overlapping-looking concepts.
- Defender/AV/indexers, file sharing modes, path normalization, network shares, profile redirection and service startup can materially affect I/O latency and locking.
- Common production symptoms: PATH resolves wrong executable, DLL search loads wrong copy, file replace fails because another process holds a handle, long/UNC path breaks legacy API, COM call fails only from wrong apartment, service works interactively but not under service account, or code page corrupts subprocess text.

## Undefined/version migration and proof
- Windows build/version, subsystem, filesystem, policy, elevation/UAC, user/service identity and optional components are implementation context, not incidental metadata.
- Migration across Windows builds/.NET/runtime/architecture needs API availability and packaging/install qualification.
- False-positive guard: access denied can be deliberate ACL/UAC policy rather than product corruption; validate intended identity/privilege boundary.
- Negative-space check: file/registry/service entry existing is not proof the running process sees the same redirected/view/architecture-specific location.
- Instrumentation should include resolved executable/DLL paths, ProcMon/ETW/Event Log where appropriate, process token/architecture, exact Win32 error and handle/resource counts.
- Learning motifs should retain OS build, architecture, identity and resolution path for recurring path/locking/COM/service failures.


---

# RESOLVED PACK: format.markdown

## PACK DOCUMENT: CONCERNS.md

# markdown Depth-5 Format Concerns

This pack augments the complete HTE-Code v2 Depth-5 baseline. It must be composed with the actual language, compiler/runtime, platform and repo authority.

## High-signal failure mechanics
- Markdown has competing dialects/extensions; CommonMark/GFM/front matter/wiki/task/math/MDX behavior must be scoped to the actual renderer.
- Blank lines, indentation and list continuation rules can change block structure unexpectedly.
- Code fences need language and delimiter lengths that safely contain embedded fence text.
- HTML-in-Markdown support and sanitization differ by renderer and trust boundary.
- Link/reference definitions can resolve far from use and duplicate labels have dialect-specific behavior.
- Autolinks, bare URLs, underscores and emphasis parsing produce renderer-dependent edge cases.
- Tables/task lists/strikethrough are extensions rather than universal core syntax.
- Relative links/images resolve against repository/site/render context, not the author's editor cwd.
- Front matter is another format layer whose delimiter/schema belongs to the site/toolchain.
- Generated documentation can be syntactically valid Markdown but semantically stale or falsely claim runtime evidence.
- Qualification renders with the actual documentation/site pipeline and verifies links, code blocks, headings and truth against implementation.


## PACK DOCUMENT: DEPTH5.md

# HTE-Code Format Pack: markdown

**Baseline:** HTE-Code v2 Depth 5
**Role:** format-specific augmentation; all other detected packs remain additive.
**Maturity:** seeded

## Signature concern catalog

### dialect

**Mechanism:** CommonMark/GFM/tool-specific extensions differ in tables, task lists, HTML and link parsing.

**Detection:** identify renderer.

**Adversarial edge:** nested list/fence/table edge.

**Qualification:** render fixture.

### code-fence

**Mechanism:** Fenced examples can become stale or syntactically invalid while document still renders.

**Detection:** extract and test executable snippets where claims depend on them.

**Adversarial edge:** versioned CLI/API example.

**Qualification:** doc-test.

### truth

**Mechanism:** Documentation is an evidence claim surface; aspirational prose must not be mistaken for implemented behavior.

**Detection:** cross-link strong claims to code/tests/runtime evidence.

**Adversarial edge:** feature described but absent.

**Qualification:** feature-truth audit.

## Depth-5 rules

- Resolve exact version/configuration/consumer before universalizing behavior.
- Separate declaration/configuration/loading from actual execution and observable effect.
- Run negative-space checks for configured-but-unused, loaded-but-unconsumed and tested-but-unexercised paths.
- Preserve exact evidence tier for build, static, integration and runtime claims.
- Add repo-learned failure motifs back into this pack only when they generalize beyond one repository.


## PACK DOCUMENT: FULL-COVERAGE.md

# Full Coverage Addendum
- **Undefined/implementation-defined behavior:** Markdown outside a fixed dialect is implementation-defined by the renderer and extension set. Even under CommonMark/GFM, HTML sanitization, heading-ID generation, syntax highlighting, link rewriting and plugin directives are hosting-tool behavior rather than universal Markdown semantics.


## PACK DOCUMENT: GAPS.md

# Markdown Depth-5 Gap Closure

## Parser, dialect, and control behavior
- Markdown has no single universal parser behavior. CommonMark, GFM, MDX, MkDocs, GitHub rendering, static-site generators, and custom renderers differ on HTML passthrough, tables, task lists, autolinks, heading IDs, footnotes, and extension syntax.
- Parsing is block-then-inline grammar, so indentation, blank lines, fence length, list nesting, and embedded HTML can change the token tree far from the apparent edit.
- Generated documentation pipelines may preprocess templates, includes, front matter, directives, or code fences before Markdown parsing. Source text is therefore not always the final document input.

## Types, representations, and persistence
- Front matter is a separate schema surface, typically YAML/TOML/JSON, with its own type coercion and migration behavior.
- Links, anchors, paths, Unicode normalization, and percent-encoding form a persisted representation contract across files, sites, and platforms.
- Numeric-looking content should not be treated as numeric data unless a consuming tool explicitly parses it; examples containing overflow, NaN, signed width, or precision claims need executable evidence outside Markdown.

## Runtime, ecosystem, and interoperability
- Embedded HTML, Mermaid, MathJax, JSX/MDX, shortcodes, and fenced executable snippets create ABI/interop-like boundaries with other parsers and runtimes.
- Renderer libraries and plugins are part of the behavior surface. A document valid in one ecosystem can fail or render differently after a dependency upgrade.
- Large generated tables, embedded data URIs, or huge fenced logs can create performance and memory pressure in editors, CI renderers, or static-site builds.

## Failure signatures and instrumentation
- Common production symptoms include broken heading links after rename, fences swallowing following sections, tables collapsing because of pipe escaping, list numbering reset by indentation, and docs that render locally but fail on the publishing renderer.
- Instrumentation should include the actual renderer/build command, link checker, snippet extraction tests, and rendered DOM/HTML inspection where layout or anchors matter.
- A false positive is a stylistic linter complaint that the target renderer intentionally accepts; guard by qualifying against the configured renderer and extension set.

## Migration, negative-space, and learning
- Migration between Markdown engines must diff rendered structure, anchors, code blocks, front matter, and embedded HTML rather than only source text.
- Negative-space check: a documented command, option, feature, or API is not implemented merely because the Markdown says it exists.
- Learning motifs should record recurring stale-command, stale-path, broken-anchor, and docs-vs-runtime mismatches so later repo audits target them first.


---

# RESOLVED PACK: protocol.http-rest

## PACK DOCUMENT: CONCERNS.md

# http-rest Depth-5 Protocol Concerns

This protocol pack augments the complete HTE-Code v2 Depth-5 baseline.
Protocol correctness includes framing/schema, state, timing, authority, retries,
partial failure, library/runtime implementation, platform/network behavior,
and application semantics. A successful API call is not proof of protocol correctness.

## High-signal failure mechanics
- Identity/version: HTTP/1.1, HTTP/2, HTTP/3, proxy/CDN behavior, API version, media type and auth scheme are separate compatibility axes.
- Parser/framing: Content-Length, chunked transfer, compression, trailers, header folding/normalization and body charset must be interpreted by the actual client/server stack.
- Method semantics: safety, idempotency and cacheability differ by method and endpoint contract; retry policy must not duplicate non-idempotent side effects.
- Redirect semantics: 301/302/303/307/308 differ in method/body preservation; credentials and sensitive headers must not cross authority unexpectedly.
- Status semantics: transport success, HTTP status success, schema-valid response and domain success are four distinct layers.
- Header state: Content-Type, Accept, Authorization, Cookie, Cache-Control, ETag/If-Match, Range and CORS headers materially alter behavior.
- Numeric limits: status codes, Content-Length, pagination limits, retry counts, timeout units and rate-limit counters need width/bounds checks.
- Streaming lifetime: response bodies own sockets/buffers until consumed/disposed; partial reads, abandoned streams and cancellation can exhaust pools.
- Concurrency: connection pooling, HTTP/2 multiplexing, per-host limits and shared retry/rate-limit state can produce head-of-line or stampede behavior.
- Errors/recovery: DNS, connect, TLS, timeout, reset, malformed response, 4xx, 5xx and domain errors require different retry/escalation rules.
- Serialization: JSON/XML/form/multipart encoders must match schema, content type, charset and absent/null/empty semantics.
- Security: URL construction, SSRF, header injection, request smuggling, open redirects, credential leakage, cookie scope and TLS verification are trust boundaries.
- Platform/network: proxies, IPv4/IPv6, corporate TLS interception, DNS caching, MTU and mobile network changes can alter runtime behavior.
- Libraries: wrapper defaults for redirects, decompression, cookie jars, pooling and timeout semantics vary by framework/version.
- Performance: connection reuse, streaming vs buffering, compression, pagination and retry/backoff determine latency, memory and throughput.
- Failure signatures: 400 often indicates contract/input mismatch; 401/403 authority; 404 routing/version; 409/412 concurrency/precondition; 429 throttling; 5xx server or intermediary failure.
- Migration: API/media-type/version deprecation, pagination changes and default-field additions need old/new client compatibility tests.
- Negative-space: route declared, client generated, or response parsed does not prove the intended endpoint is called or its result is consumed.
- False-positive guard: repeated GET retries or 404 handling can be correct when the endpoint contract explicitly defines them; do not label patterns without method/domain context.
- Learning motif: record recurring endpoint-specific status fingerprints, proxy quirks and retry failures only after reproduced evidence across runs.


## PACK DOCUMENT: DEPTH5.md

# HTE-Code Protocol Pack: http-rest

**Baseline:** HTE-Code v2 Depth 5
**Role:** protocol-specific augmentation; language/runtime/toolchain packs remain additive.
**Maturity:** seeded

## Signature concern catalog

### status

**Mechanism:** HTTP transport success, application success and semantic success are distinct; redirects/retries/idempotency matter.

**Detection:** trace method/status/redirect/retry policy.

**Adversarial edge:** 3xx/4xx/5xx, timeout after server commit.

**Qualification:** mock + real endpoint failure matrix.

### headers

**Mechanism:** Content-Type, Accept, auth, cache and conditional headers change representation/authority.

**Detection:** inspect exact request/response headers without secrets.

**Adversarial edge:** missing charset, stale ETag, auth expiry.

**Qualification:** wire-level integration.

### body

**Mechanism:** Streaming/body ownership, size limits and partial reads affect memory and correctness.

**Detection:** trace buffering/stream lifetime.

**Adversarial edge:** oversized/chunked/truncated body.

**Qualification:** bounded streaming tests.



## PACK DOCUMENT: FULL-COVERAGE.md

# Full Coverage Addendum
- **Undefined/implementation-defined:** 'REST' adds application conventions beyond HTTP and is not a wire standard itself. Proxy/cache retry behavior, redirect policy, connection pooling, DNS/TLS and JSON/date/error envelopes are client/server implementation choices that must be recorded explicitly.
