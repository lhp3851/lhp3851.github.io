---
title: iOS之LLDB
abbrlink: bc630799
date: 2021-04-20 21:36:02
tags:
---

Debugger commands:
  apropos           -- List debugger commands related to a word or subject.
  breakpoint        -- Commands for operating on breakpoints (see 'help b' for shorthand.)
  bugreport         -- Commands for creating domain-specific bug reports.
  command           -- Commands for managing custom LLDB commands.
  disassemble       -- Disassemble specified instructions in the current target.  Defaults to the current function for the current thread and stack frame.
  expression        -- Evaluate an expression on the current thread.  Displays any returned value with LLDB's default formatting.
  frame             -- Commands for selecting and examing the current thread's stack frames.
  gdb-remote        -- Connect to a process via remote GDB server.  If no host is specifed, localhost is assumed.
  gui               -- Switch into the curses based GUI mode.
  help              -- Show a list of all debugger commands, or give details about a specific command.
  kdp-remote        -- Connect to a process via remote KDP server.  If no UDP port is specified, port 41139 is assumed.
  language          -- Commands specific to a source language.
  log               -- Commands controlling LLDB internal logging.
  memory            -- Commands for operating on memory in the current target process.
  platform          -- Commands to manage and create platforms.
  plugin            -- Commands for managing LLDB plugins.
  process           -- Commands for interacting with processes on the current platform.
  quit              -- Quit the LLDB debugger.
  register          -- Commands to access registers for the current thread and stack frame.
  script            -- Invoke the script interpreter with provided code and display any results.  Start the interactive interpreter if no code is supplied.
  settings          -- Commands for managing LLDB settings.
  source            -- Commands for examining source code described by debug information for the current target process.
  statistics        -- Print statistics about a debugging session
  target            -- Commands for operating on debugger targets.
  thread            -- Commands for operating on one or more threads in the current process.
  type              -- Commands for operating on the type system.
  version           -- Show the LLDB debugger version.
  watchpoint        -- Commands for operating on watchpoints.
Current command abbreviations (type 'help command alias' for more info):
  add-dsym  -- Add a debug symbol file to one of the target's current modules by specifying a path to a debug symbols file, or using the options to specify a module to download symbols for.
  attach    -- Attach to process by ID or name.
  b         -- Set a breakpoint using one of several shorthand formats.
  bt        -- Show the current thread's call stack.  Any numeric argument displays at most that many frames.  The argument 'all' displays all threads.
  c         -- Continue execution of all threads in the current process.
  call      -- Evaluate an expression on the current thread.  Displays any returned value with LLDB's default formatting.
  continue  -- Continue execution of all threads in the current process.
  detach    -- Detach from the current target process.
  di        -- Disassemble specified instructions in the current target.  Defaults to the current function for the current thread and stack frame.
  dis       -- Disassemble specified instructions in the current target.  Defaults to the current function for the current thread and stack frame.
  display   -- Evaluate an expression at every stop (see 'help target stop-hook'.)
  down      -- Select a newer stack frame.  Defaults to moving one frame, a numeric argument can specify an arbitrary number.
  env       -- Shorthand for viewing and setting environment variables.
  exit      -- Quit the LLDB debugger.
  f         -- Select the current stack frame by index from within the current thread (see 'thread backtrace'.)
  file      -- Create a target using the argument as the main executable.
  finish    -- Finish executing the current stack frame and stop after returning.  Defaults to current thread unless specified.
  image     -- Commands for accessing information for one or more target modules.
  j         -- Set the program counter to a new address.
  jump      -- Set the program counter to a new address.
  kill      -- Terminate the current target process.
  l         -- List relevant source code using one of several shorthand formats.
  list      -- List relevant source code using one of several shorthand formats.
  n         -- Source level single step, stepping over calls.  Defaults to current thread unless specified.
  next      -- Source level single step, stepping over calls.  Defaults to current thread unless specified.
  nexti     -- Instruction level single step, stepping over calls.  Defaults to current thread unless specified.
  ni        -- Instruction level single step, stepping over calls.  Defaults to current thread unless specified.
  p         -- Evaluate an expression on the current thread.  Displays any returned value with LLDB's default formatting.
  parray    -- Evaluate an expression on the current thread.  Displays any returned value with LLDB's default formatting.
  po        -- Evaluate an expression on the current thread.  Displays any returned value with formatting controlled by the type's author.
  poarray   -- Evaluate an expression on the current thread.  Displays any returned value with LLDB's default formatting.
  print     -- Evaluate an expression on the current thread.  Displays any returned value with LLDB's default formatting.
  q         -- Quit the LLDB debugger.
  r         -- Launch the executable in the debugger.
  rbreak    -- Sets a breakpoint or set of breakpoints in the executable.
  repl      -- Evaluate an expression on the current thread.  Displays any returned value with LLDB's default formatting.
  run       -- Launch the executable in the debugger.
  s         -- Source level single step, stepping into calls.  Defaults to current thread unless specified.
  si        -- Instruction level single step, stepping into calls.  Defaults to current thread unless specified.
  sif       -- Step through the current block, stopping if you step directly into a function whose name matches the TargetFunctionName.
  step      -- Source level single step, stepping into calls.  Defaults to current thread unless specified.
  stepi     -- Instruction level single step, stepping into calls.  Defaults to current thread unless specified.
  t         -- Change the currently selected thread.
  tbreak    -- Set a one-shot breakpoint using one of several shorthand formats.
  undisplay -- Stop displaying expression at every stop (specified by stop-hook index.)
  up        -- Select an older stack frame.  Defaults to moving one frame, a numeric argument can specify an arbitrary number.
  v         -- Show variables for the current stack frame. Defaults to all arguments and local variables in scope. Names of argument, local, file static and file global variables can be specified. Children of aggregate variables can be specified such as
               'var->child.x'.  The -> and [] operators in 'frame variable' do not invoke operator overloads if they exist, but directly access the specified element.  If you want to trigger operator overloads use the expression command to print the variable
               instead.
               It is worth noting that except for overloaded operators, when printing local variables 'expr local_var' and 'frame var local_var' produce the same results.  However, 'frame variable' is more efficient, since it uses debug information and memory
               reads directly, rather than parsing and evaluating an expression, which may even involve JITing and running code in the target program.
  var       -- Show variables for the current stack frame. Defaults to all arguments and local variables in scope. Names of argument, local, file static and file global variables can be specified. Children of aggregate variables can be specified such as
               'var->child.x'.  The -> and [] operators in 'frame variable' do not invoke operator overloads if they exist, but directly access the specified element.  If you want to trigger operator overloads use the expression command to print the variable
               instead.
               It is worth noting that except for overloaded operators, when printing local variables 'expr local_var' and 'frame var local_var' produce the same results.  However, 'frame variable' is more efficient, since it uses debug information and memory
               reads directly, rather than parsing and evaluating an expression, which may even involve JITing and running code in the target program.
  vo        -- Show variables for the current stack frame. Defaults to all arguments and local variables in scope. Names of argument, local, file static and file global variables can be specified. Children of aggregate variables can be specified such as
               'var->child.x'.  The -> and [] operators in 'frame variable' do not invoke operator overloads if they exist, but directly access the specified element.  If you want to trigger operator overloads use the expression command to print the variable
               instead.
               It is worth noting that except for overloaded operators, when printing local variables 'expr local_var' and 'frame var local_var' produce the same results.  However, 'frame variable' is more efficient, since it uses debug information and memory
               reads directly, rather than parsing and evaluating an expression, which may even involve JITing and running code in the target program.
  x         -- Read from the memory of the current target process.
For more information on any command, type 'help <command-name>'.