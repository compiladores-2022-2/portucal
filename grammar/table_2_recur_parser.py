from utils import *

def process_body_el(name):
  if "\"" in name:
    return f"eat({str2token_enum(name)});"
  elif name == "#vazio#":
    return ""
  else:
    return f"_{name}();"
  

def gen_rule(rule):
  _, body = rule.split("::=")
  body = [
    process_body_el(x.strip()) 
    for x in body.strip().split()
  ]
  return " ".join(body) + " break;\n"


def parse(fname, lines):
  output = f"void _{fname}(){{ switch (tok) {{\n"

  rule2tokens = dict()
  for line in lines:
    token, rule = (x.strip() for x in line.strip().split("=>"))
    if not rule in rule2tokens:
      rule2tokens[rule] = []
    rule2tokens[rule].append(token)

  for rule, tokens in rule2tokens.items():
    for i, token in enumerate(tokens):
      output += f"\tcase {str2token_enum(token)}:"
      if i + 1 < len(tokens): output += "\n"
    
    output += "{\n\t\t"
    output += gen_rule(rule)
    output += "\t}\n"

  output += "\tdefault: error();\n"
  output += "}}"

  return output
  

def gen_declr(name):
  return f"void _{name}();"

def __main__():
  funcs = []
  with open("simple_table", "r") as f:
    curr_lines = []
    curr_name = ""

    for line in f.readlines():
      line = line.strip()
      if line == "================================":
        funcs.append((parse(curr_name, curr_lines), curr_name))
        curr_name = ""
        curr_lines = []
      elif curr_name == "":
        curr_name = line.split()[1].strip()
      else:
        curr_lines.append(line)

  funcs = sorted(funcs, key= lambda x : x[1])
        
  for _, name in funcs:
    print(gen_declr(name))
  
  print("\n\n")

  for impl, _ in funcs:
    print(impl, "\n")



__main__()
  