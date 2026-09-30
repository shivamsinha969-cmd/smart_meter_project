# Stage 2 — Development Plan

## Working approach
Complete the project in small checkpoints. Record each checkpoint in Git and update the progress log. Keep the `main` branch for completed, working milestones. Use a short feature branch for a larger change, then merge it into `main` after checking it.

## Milestones
| Milestone | Work | Evidence |
|---|---|---|
| Stage 1 | Explain the project idea, problem, scope, and outcome | `stage1_introduction.md` and Git commit |
| Stage 2 | Define requirements, scope, modules, deliverables, and schedule | Requirements and development-plan documents |
| Stage 3 | Design architecture, data flow, data structures, and UML; confirm tools and Git workflow | Design documents and diagrams |
| Stage 4 | Build the initial virtual driver and C++ reader; demonstrate simulated readings | Source code, build output, and demo notes |
| Stage 5 | Test driver and application, fix issues, and improve error handling | Test results, issue notes, and sample CSV |
| Stage 6 | Finalize documentation and prepare the complete demonstration and presentation | Final report, presentation, and demo checklist |

## Suggested schedule
- Week 1: Stages 1–2 — introduction, requirements, and plan.
- Week 2: Stage 3 — architecture and diagrams.
- Weeks 3–4: Stage 4 — initial driver and C++ prototype.
- Week 5: Stage 5 — testing and improvements.
- Week 6: Stage 6 — final report, demonstration, and presentation.

The schedule is an estimate. If implementation or debugging takes longer, update the progress log and adjust the remaining milestones.

## Git workflow
- `main` contains the latest completed milestone.
- For a larger feature, create a branch such as `stage-4-driver`.
- Build and check the feature on that branch.
- Merge it into `main` when the checkpoint is working.
- Use clear commits, for example: `docs: add stage 2 requirements`.

## Progress tracking
For each work session, record the date, completed work, commands or checks performed, problems encountered, and the next task in `docs/progress.md`.
