MRuby::Gem::Specification.new('mruby-tflite-xnnpack') do |spec|
  spec.license = 'MIT'
  spec.authors = 'mattn'

  spec.linker.libraries << 'tensorflowlite-delegate_xnnpack' << 'XNNPACK'
end
