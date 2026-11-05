# Documentation Plan for a Collaborative Computing Project

This plan is a reusable starting point for a student team building a shared software project, such as a numerical library, scientific application, or set of computational tools. It is based on the organization and documentation practices in this repository. Replace the bracketed prompts and adjust the schedule to fit the group, course requirements, and project size.

## 1. Purpose and audience

Documentation should help a new team member, user, reviewer, or maintainer answer:

- What does the project do, and how do I build and run it?
- How is the code organized, and how do its components work together?
- What does each public module provide, and how should I use it?
- What assumptions, limitations, and errors should I expect?
- How was the software tested, and how can I reproduce the results?
- Who is responsible for each deliverable, and what remains unfinished?

Write for readers who may not have attended the group's meetings. Explain project-specific terms, link related material, and avoid relying on chat history or undocumented knowledge.

## 2. Documentation principles

1. **Keep one clear source of truth.** Put current instructions and project facts in the repository. Link to them instead of copying the same information into several files.
2. **Document as the project develops.** Update a module guide when its interface or behavior changes; do not leave all documentation until the final week.
3. **Assign an owner and a reviewer.** The contributor drafts the documentation for their work. A different member checks accuracy, completeness, and whether the instructions work.
4. **Describe actual behavior.** Verify names, parameters, return values, exceptions, examples, and test results against the implementation.
5. **Use diagrams to clarify relationships.** Show component boundaries, dependencies, shared helpers, and meaningful inheritance. Do not imply relationships that the design does not have.
6. **Make verification reproducible.** Give the commands, inputs, environment assumptions, and expected results needed to repeat a build or test.
7. **Separate plans, progress, and results.** A plan says what should happen; weekly reports say what did happen; final reports summarize verified outcomes.

## 3. Deliverables and suggested repository layout

Adapt this structure to the project. Keep the top-level README short enough to work as an entry point.

```text
README.md
docs/
  README.md                 # Documentation index and project overview
  architecture.md           # Components, relationships, and design decisions
  algorithms.md             # Methods, assumptions, accuracy, and complexity
  testing.md                # Test strategy, results, and reproduction commands
  documentation-plan.md     # This plan, adapted for the team
  modules/
    <module-name>.md        # One guide per public module or coherent feature
  examples.md               # Example catalog and how to run examples
  reports/
    week-<n>.md             # Progress, blockers, and next steps
    final-report.md         # Final scope, outcomes, and lessons
  diagrams/
    <diagram-name>.<format>
```

Generated reference documentation (for example, Doxygen output) may be built from comments in the source code. Document how to generate it, but do not commit generated output unless the team has agreed that it should be versioned.

| Deliverable | Minimum contents | Suggested owner |
|---|---|---|
| Top-level README | Purpose, features, prerequisites, build/run/test quick start, links to detailed docs | Project lead or editor |
| Documentation index | Project overview, documentation map, component/method catalog, links to reports and generated reference | Documentation coordinator |
| Architecture guide and diagrams | Components, public interfaces, dependencies, shared helpers, errors, and design decisions | Architecture owner, reviewed by contributors |
| Module guides | Purpose, interface, algorithm or behavior, inputs, outputs, errors, limitations, example, tests | Module contributor, reviewed by another member |
| Algorithm or design report | Rationale, method, assumptions, accuracy/cost where relevant, alternatives, safeguards | Technical contributors |
| Examples guide | Example inventory, prerequisites, commands, expected behavior, relationship to modules | Example owners |
| Testing guide and results | Test levels, normal/edge/invalid cases, measurable properties, commands, environment, outcomes | QA/test lead |
| Progress reports | Completed work, in-progress work, blockers and resolutions, next steps, member contributions, required AI-use disclosure | Each member; compiled by coordinator |
| Final report | Delivered scope, architecture, verification evidence, limitations, contributions, lessons learned | Whole group; editor consolidates |

## 4. Work assignment and review

At project kickoff, create a documentation tracker with one row per deliverable or module:

| Item | Primary author | Reviewer | Due phase | Status | Source or implementation link |
|---|---|---|---|---|---|
| [Module or document] | [Name] | [Different name] | [Phase/date] | Not started / Draft / Review / Verified | [Path or link] |

Assign work by component or module, not only by document type. The person implementing a component is usually best placed to draft its guide; a separate reviewer should check correctness. Keep the QA role independent where possible, especially for high-risk or complex components. The documentation coordinator maintains the index and checks consistency, but does not need to author every technical guide.

For every assigned item, record:

- the implementation and tests it covers;
- the author and reviewer;
- the expected format and repository location;
- the acceptance checks from Section 7;
- any dependencies, such as a stable interface or verified test result.

## 5. Phased schedule

Use project milestones rather than fixed calendar weeks. A short project can combine phases; a longer project can repeat the implementation and verification phases.

### Phase A — Kickoff and scope

- Agree on the project purpose, intended audience, deliverables, and documentation location.
- Create the repository skeleton and documentation tracker.
- Record team roles, module ownership, review assignments, and communication cadence.
- Draft the README outline and list the planned modules, methods, examples, and tests.
- Capture unresolved design questions rather than documenting assumptions as settled facts.

**Exit check:** Every planned component has an owner; the project has a documentation map and an agreed review workflow.

### Phase B — Interface and architecture

- Agree on naming, file layout, public interfaces, shared types/helpers, and error conventions.
- Create an architecture overview and an initial diagram of classes or components.
- Record meaningful dependencies and explain whether inheritance, composition, or standalone helpers are used.
- Document design changes when they occur. If the design changes, update the diagram and affected guides in the same change.

**Exit check:** Contributors can implement compatible modules, and the diagrams represent the agreed design.

### Phase C — Implementation and module documentation

For each module or feature:

- Implement the feature and stabilize its public interface.
- Write source-level API comments using the project's chosen convention.
- Draft its module guide: purpose, interface, behavior, input constraints, outputs, exceptions, limitations, and a small working example.
- Add normal, boundary, and invalid-input tests as appropriate.
- Ask a teammate to review both the code and its documentation before integration.

**Exit check:** The module builds, its tests pass, and the guide agrees with the implementation.

### Phase D — Examples and integration

- Add at least one usable example for each major public feature or coherent module.
- Explain how to build/run examples and what output or behavior to expect.
- Maintain a shared-helper guide if common validation, iteration, or data-handling code is introduced.
- Update the architecture overview and module catalog as integration reveals missing or changed components.
- Check that the README's commands and links work from a clean checkout.

**Exit check:** A new user can discover, build, and run representative features without relying on a contributor.

### Phase E — Verification and results

- Run the complete supported build and test workflow on the agreed environments.
- Record commands, compiler/tool versions where relevant, pass/fail counts, and known limitations.
- Test mathematical or domain-specific properties, not just example outputs (for example, convergence order, conservation, error tolerance, or invariants).
- Run generated-reference documentation checks, such as Doxygen warnings, when configured.
- Fix discrepancies between the results, implementation, and documentation; do not report unverified claims as results.

**Exit check:** The recorded results can be reproduced and all release-blocking failures are resolved or explicitly documented.

### Phase F — Final review and handover

- Consolidate progress reports into a final report and confirm contribution records with the group.
- Check spelling, terminology, filenames, links, diagram labels, and command accuracy.
- Review the repository from the perspective of a new user and a future maintainer.
- State what is complete, what is out of scope, and what should be done next.
- Tag or otherwise identify the reviewed documentation version according to the group's release process.

**Exit check:** Documentation is internally consistent, discoverable, and adequate for a new group to build on the work.

## 6. Reusable content checklist

### Project README

- [ ] One-paragraph project purpose and audience.
- [ ] Main capabilities and important limitations.
- [ ] Prerequisites and supported environment.
- [ ] Copyable build, run, and test instructions.
- [ ] Repository layout at a useful level of detail.
- [ ] Links to architecture, module guides, examples, testing, and reports.
- [ ] Maintainer or group contact/ownership information, if appropriate.

### Architecture guide and diagrams

- [ ] Main components and their responsibilities.
- [ ] Public classes/modules and important operations.
- [ ] Shared helpers and which components use them.
- [ ] Dependency direction and data flow where useful.
- [ ] Inheritance relationships only where they actually exist.
- [ ] Exception/error flow and relevant validation boundaries.
- [ ] Diagram title, legend, and enough labels to interpret it without the author.
- [ ] Diagram and prose updated after design changes.

### Module guide

- [ ] Problem solved and appropriate use cases.
- [ ] Public API with parameter meanings, units/domains, return shape, and side effects.
- [ ] Preconditions, validation, exceptions, and failure behavior.
- [ ] Algorithm or internal approach at the level readers need.
- [ ] Assumptions, accuracy/performance characteristics, and limitations where applicable.
- [ ] Minimal example that compiles or otherwise runs.
- [ ] Links to related modules, tests, and source reference.

### Testing guide and evidence

- [ ] Scope of unit, integration, end-to-end, and example tests.
- [ ] Normal, edge/boundary, and invalid-input coverage.
- [ ] Domain-specific properties and numerical tolerances where applicable.
- [ ] Exact command to run tests from a clean checkout.
- [ ] Test/build environment and dependencies.
- [ ] Results are dated or tied to a revision and distinguish pass, fail, and not run.
- [ ] Known failures or untested areas are stated explicitly.

### Progress and final reports

- [ ] Completed, in-progress, and next work are separated.
- [ ] Contributions identify outcomes, not only activity.
- [ ] Blockers include impact and resolution or requested help.
- [ ] Major design decisions and changes are recorded with links.
- [ ] AI/tool use is disclosed when required by the course or institution, including tool and purpose.
- [ ] Final report reflects the integrated project, not just individual weekly notes.

## 7. Definition of done for documentation

A documentation item is complete when:

1. It is in the agreed repository location and discoverable from the index or README.
2. Names, signatures, behavior, and error handling match the current implementation.
3. Commands and examples have been checked against the supported workflow.
4. Claims about results are supported by recorded tests or other evidence.
5. Relevant links and diagrams are current.
6. A teammate other than the author has reviewed it.
7. The change is integrated through the group's normal version-control review process.

Before handover, check for undocumented public interfaces, stale TODOs, broken links, duplicate or contradictory instructions, and generated files that should not be committed.

## 8. Suggested weekly reporting format

Use a concise, consistent report. Keep individual contributions factual and link to code, tests, and documentation where possible.

```markdown
# [Project] — [Week or milestone]

## Completed
- [Outcome, contributor, and relevant link]

## In progress
- [Work remaining, owner, and expected next step]

## Blockers and decisions
- [Issue, impact, action taken or help needed]

## Verification
- [Build/test/documentation command and result, or "not run" with reason]

## Next milestone
- [Specific deliverable and owner]

## Tool/AI use
- [Tool, purpose, and disclosure required by course policy; otherwise state none]
```

## 9. Tailoring this plan

For a different group or project:

- Replace module names with the actual components, features, or research work.
- Scale the number of guides to the public surface; combine small related features when that improves navigation.
- Replace Doxygen with the language's established documentation tool, if applicable.
- Keep mathematical convergence and numerical-error checks only where the domain calls for them; use equivalent domain properties for other software.
- Adjust phase duration, contributor roles, reporting format, and AI-use disclosure to course and institutional requirements.
- Preserve the core practice: every important claim should have an owner, a reviewer, and a way to verify it.

## 10. Basis in the source material

This plan adapts practices visible in this repository's [documentation index](README.md), [testing approach](testing.md), [algorithm report](algorithm-report.md), [module guides](modules/), and [weekly and final reports](../reports/). The source material includes module-level guides, class and helper relationship diagrams, source-level API documentation, reproducible tests and examples, issue/debug records, and member-by-member progress reporting. These are treated here as reusable patterns, not requirements that every group must copy unchanged.
