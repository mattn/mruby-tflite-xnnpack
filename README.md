# mruby-tflite-xnnpack

XNNPACK interface to TensorFlow Lite for mruby

## Usage

```ruby
options = TfLite::InterpreterOptions.new
options.add_delegate TfLite::XNNPACK.new(4) # 4 threads
model = TfLite::Model.from_file 'detect.tflite'
interpreter = TfLite::Interpreter.new(model, options)
```

## Requirements

* TensorFlow Lite
* XNNPACK
* mruby-tflite

## License

MIT

## Author

Yasuhiro Matsumoto (a.k.a. mattn)
