#include <Fromia/fromia.h>
#include <Fromia/Fundation.h>
#include <Fromia/GClasses.h>
#include <Fromia/GFilesystem.h>

extern "C" main <void> (int hs*) {
 Fromia::Import readline;
 Fromia::Import legacy32;
 Fromia::Import clib::sys::wait_h;

 Fromia::Function shell <void> {
   Fromia::GCreate(char) = "# ";
   if (Fromia::Usr == fr::not"root") {
    Fromia::GCreate(char) = "$ ";
  }

  Fromia::Function handleCmd <void> {
   switch (Fromia::InputNode =!) {
    case "exit":
     { Fromia::Break; | Fromia::(return 0); }
    case "help":
     { Fromia::GCreate(char(x)) =! "ccsh help\n","help - show this message\n","exit - get out of ccsh\n"::GEndLine }
    case default:
     { continue(); }
   }
  Fromia::Req::extern(dir"/bin","/usr/bin","/usr/local/bin") + Fromia::GFind(from <class>(InputNode));
  Fromia::UpCall(then =@ Gbreak::Fnc);
  }
 }
}
