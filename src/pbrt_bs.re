open Js.Json;

module E = {
  type error =
    | Unexpected_json_type(string, string)
    | Malformed_variant(string);

  exception Failure(error);
  let unexpected_json_type = (record_name, field_name) =>
    raise(
      Failure(
        [@implicit_arity] Unexpected_json_type(record_name, field_name),
      ),
    );
  let malformed_variant = variant_name =>
    raise(Failure(Malformed_variant(variant_name)));
  let string_of_error =
    fun
    | [@implicit_arity] Unexpected_json_type(record_name, field_name) =>
      Printf.sprintf(
        "Unexpected json type (record name:%s, field_name:%s)",
        record_name,
        field_name,
      )
    | Malformed_variant(variant_name) =>
      Printf.sprintf("Malformed variant (variant name: %s)", variant_name);
  let () =
    Printexc.register_printer(exn =>
      switch (exn) {
      | Failure(e) => Some(string_of_error(e))
      | _ => None
      }
    );
};

let int32_ = (ty, record_name, field_name) =>
  switch (ty) {
  | JSONString(v) => Int32.of_string(v)
  | JSONNumber(v) => Int32.of_float(v)
  | JSONNull => 0l
  | _ => E.unexpected_json_type(record_name, field_name)
  };

let int32 = (json, record_name, field_name) =>
  int32_(Js_json.classify(json), record_name, field_name);

let int64_ = (ty, record_name, field_name) =>
  switch (ty) {
  | JSONString(v) => Int64.of_string(v)
  | JSONNumber(v) => Int64.of_float(v)
  | JSONNull => 0L
  | _ => E.unexpected_json_type(record_name, field_name)
  };

let int64 = (json, record_name, field_name) =>
  int64_(Js_json.classify(json), record_name, field_name);

let float_ = (ty, record_name, field_name) =>
  switch (ty) {
  | JSONString(v) => float_of_string(v)
  | JSONNumber(v) => v
  | JSONNull => 0.0
  | _ => E.unexpected_json_type(record_name, field_name)
  };

let float = (json, record_name, field_name) =>
  float_(Js_json.classify(json), record_name, field_name);

let int_ = (ty, record_name, field_name) =>
  switch (ty) {
  | JSONString(v) => int_of_string(v)
  | JSONNumber(v) => int_of_float(v)
  | JSONNull => 0
  | _ => E.unexpected_json_type(record_name, field_name)
  };

let int = (json, record_name, field_name) =>
  int_(Js_json.classify(json), record_name, field_name);

let bool_ = (ty, record_name, field_name) =>
  switch (ty) {
  | JSONTrue => true
  | JSONFalse => false
  | _ => E.unexpected_json_type(record_name, field_name)
  };

let bool = (json, record_name, field_name) =>
  bool_(Js_json.classify(json), record_name, field_name);

let string_ = (ty, record_name, field_name) =>
  switch (ty) {
  | JSONString(v) => v
  | JSONNull => ""
  | _ => E.unexpected_json_type(record_name, field_name)
  };

let string = (json, record_name, field_name) =>
  string_(Js_json.classify(json), record_name, field_name);

let bytes = (_, record_name, field_name) =>
  E.unexpected_json_type(record_name, field_name);

let object__ = (ty, record_name, field_name) =>
  switch (ty) {
  | JSONObject(v) => v
  | JSONNull => Js_dict.empty()
  | _ => E.unexpected_json_type(record_name, field_name)
  };

let object_ = (json, record_name, field_name) =>
  object__(Js_json.classify(json), record_name, field_name);

let array__ = (ty, record_name, field_name) =>
  switch (ty) {
  | JSONArray(v) => v
  | JSONNull => [||]
  | _ => E.unexpected_json_type(record_name, field_name)
  };

let array_ = (json, record_name, field_name) =>
  array__(Js_json.classify(json), record_name, field_name);