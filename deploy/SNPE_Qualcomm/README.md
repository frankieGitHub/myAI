# tensorflow convertor
```
converters/tensorflow/converter.py
  class DlcConverter
    def convert
      _convert_input_layers
        descriptor = InputLayerDescriptor(layer_name, [input_operation])
        self._input_descriptors.append(descriptor)
        model.add_data_layer
      _convert_layers()
        descriptors = self._resolve_descriptors_from_nodes(graph_ops)
          resolvers = self._create_layer_resolvers()
            return [resolver_class() for resolver_class in layers.layer_resolvers]
              layer_resolvers = [ConvolutionLayerResolver,ReluLayerResolver,...]
              class ConvolutionLayerResolver
                def __init__
                  self.sequence = GraphSequence([ConverterSequenceNode('root', ['Conv2D'])])
                  self.sequence.set_outputs(['root'])
                def resolve_layer
                  matches = graph_matcher.match_sequence(self.sequence)
                  for match in matches:
                    conv_op = match['root']
                    bias_op = None
                    descriptor = ConvolutionLayerResolver.Descriptor(...)
          for resolver in resolvers:
            resolved_descriptors = resolver.resolve_layer(graph_matcher, self._graph_helper)
        _transform_descriptors(descriptors)
          for descriptor in descriptors:
            layer_builder = self._create_layer_builder(descriptor)
              builder_class = layers.layer_builders.get(type(descriptor), None)
              ===layer_builders = {BatchNormLayerResolver.Descriptor: BatchNormLayerBuilder,
              layer_builder.transform_layer(self._context, descriptor, inputs, outputs)
        _create_layers(descriptors)
          for descriptor in descriptors:
            layer_builder = self._create_layer_builder(descriptor)
            _create_layer(layer_builder, descriptor)
              layer_builder.build_layer(self._context, descriptor, inputs, outputs)
              ===class ConvolutionLayerBuilder(LayerBuilder):
              ===  def build_layer(...):
              ===    converter_context.model.add_conv_layer(name=descriptor.layer_name,...)
      self._set_model_version(model_version)
      self._context.model.set_converter_command(converter_command)
      self._context.model.save(dlc_output_path)
```

