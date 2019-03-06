module E: {
  type error =
    | Unexpected_json_type(string, string)
    | Malformed_variant(string);
  exception Failure(error);
  let unexpected_json_type: (string, string) => 'a;
  let malformed_variant: string => 'a;
  let string_of_error: error => string;
};

let int32_: (Js.Json.tagged_t, string, string) => int32;

let int32: (Js.Json.t, string, string) => int32;

let int64_: (Js.Json.tagged_t, string, string) => int64;

let int64: (Js.Json.t, string, string) => int64;

let float_: (Js.Json.tagged_t, string, string) => float;

let float: (Js.Json.t, string, string) => float;

let int_: (Js.Json.tagged_t, string, string) => int;

let int: (Js.Json.t, string, string) => int;

let bool_: (Js.Json.tagged_t, string, string) => bool;

let bool: (Js.Json.t, string, string) => bool;

let string_: (Js.Json.tagged_t, string, string) => string;

let string: (Js.Json.t, string, string) => string;

let bytes: ('a, string, string) => 'b;

let object__: (Js.Json.tagged_t, string, string) => Js.Dict.t(Js.Json.t);

let object_: (Js.Json.t, string, string) => Js.Dict.t(Js.Json.t);

let array__: (Js.Json.tagged_t, string, string) => array(Js.Json.t);

let array_: (Js.Json.t, string, string) => array(Js.Json.t);