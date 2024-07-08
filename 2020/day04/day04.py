import re


def read_and_parse(filename):
    with open(filename, "r", encoding="utf8") as f:
        lines = f.readlines()
        f.close()
    lines = list(map(str.rstrip, lines))
    c = 0
    out = [{}]
    for l in lines:
        if len(l) > 0:
            out[c].update(dict(map(lambda x: x.split(":"), l.split(" "))))
        else:
            out.append({})
            c += 1
    return out


def valid_passport(info, required_fields):
    for rf in required_fields:
        if not rf in info:
            return False
    return True


def sol1(passports):
    rf = ["byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"]
    c = 0
    for p in passports:
        if valid_passport(p, rf):
            c += 1
    return c


def field_validation(field, val):
    if field == "byr":
        val = int(val)
        if 1920 <= val <= 2002:
            return True
    elif field == "iyr":
        val = int(val)
        if 2010 <= val <= 2020:
            return True
    elif field == "eyr":
        val = int(val)
        if 2020 <= val <= 2030:
            return True
    elif field == "hgt":
        if "cm" in str(val):
            val = int(re.search(r"\d+", val).group())
            if 150 <= val <= 193:
                return True
        if "in" in str(val):
            val = int(re.search(r"\d+", val).group())
            if 59 <= val <= 76:
                return True
    elif field == "hcl":
        if re.search(r"((#){1})([0-9,a-f]{1})", val):
            return True
    elif field == "ecl":
        if val in ["amb", "blu", "brn", "gry", "grn", "hzl", "oth"]:
            return True
    elif field == "pid":
        if val.isdigit() and len(val) == 9:
            return True
    elif field == "cid":
        pass

    return False


def strict_valid_passport(info, required_fields) -> bool:
    for rf in required_fields:
        if not rf in info:
            return False
        if not field_validation(rf, info[rf]):
            return False
    return True


def sol2(passports):
    rf = ["byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"]
    c = 0
    for p in passports:
        if strict_valid_passport(p, rf):
            c += 1
    return c


def main() -> None:
    sample_input = read_and_parse("sample.input")
    print(f"sample 1: {sol1(sample_input)}")
    strict_valid_passports = read_and_parse("valid.input")
    print(f"sample 2 valid: {sol2(strict_valid_passports)}")
    strict_invalid_passports = read_and_parse("invalid.input")
    print(f"sample 2 invalid: {sol2(strict_invalid_passports)}")

    inp = read_and_parse("day04.input")
    print(f"problem 1: {sol1(inp)}")
    print(f"problem 2: {sol2(inp)}")


if __name__ == "__main__":
    main()
