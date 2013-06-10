Pod::Spec.new do |s|
  s.name         = "LibComponentLogging-TestFlight"
  s.version      = "0.0.1"
  s.summary      = "A simple LibComponentLogging logger implementation which redirects logging to TFLog."
  s.homepage     = "https://github.com/iostaf/LibComponentLogging-TestFlight.git"
  s.license      = 'MIT'
  s.author       = { "Ivan Ostafiychuk" => "iostaf@gmail.com" }
  s.source       = { :local => '.' }
  s.platform     = :ios, '5.0'
  s.source_files = '*'
end
