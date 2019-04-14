# tensorflow convertor
```
1. tensorflow model convert workflow:
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

2. how to get tensorflow ops from model?
converters/tensorflow/converter.py
class DlcConverter(object):
  def __init__:
    self._ops = self._resolve_graph_operations_from_model(model)
      operations_map = dict()
      for op in model.session.graph.get_operations():  //can not find the implement
        operations_map[str(op.name)] = op

3. why every specify lay has a sub class Descriptor?
class SliceLayerResolver(LayerResolver, object):
    class Descriptor(LayerDescriptor):
        def __init__(self, name, nodes, axis, split_sizes, split_count):
            super(SliceLayerResolver.Descriptor, self).__init__('Slice', name, nodes)
            //这里父类三个公共属性， layer type, layer name, ops
            self.axis = axis  //具体层的具体属性
            self.split_sizes = split_sizes
            self.split_count = split_count

```

```
|-- converters
|   |-- __init__.py
|   |-- code_to_message.py
|   |-- lower_to_dlc.py
|   |-- onnx
|   |   |-- __init__.py
|   |   |-- data_translations.py
|   |   |-- math_translations.py
|   |   |-- messages.py
|   |   |-- nn_translations.py
|   |   |-- onnx_to_dlc.py
|   |   |-- onnx_translations.py
|   |   |-- rnn_translations.py
|   |   `-- util.py
|   |-- op_adapter.py
|   |-- op_graph.py
|   |-- tensorflow
|   |   |-- __init__.py
|   |   |-- common.py   ===> LayerDescriptor/InputLayerDescriptor/LayerResolver/LayerBuilder
|   |   |-- converter.py    ==> tf2dlc main workflow
|   |   |-- graph_matcher.py ==> class GraphMatcher used in diff layers
|   |   |-- layers
|   |   |   |-- __init__.py
|   |   |   |-- add_n.py
|   |   |   |-- argmax.py
|   |   |   |-- batchnorm.py
|   |   |   |-- channel_shuffle.py
|   |   |   |-- concat.py
|   |   |   |-- constant.py
|   |   |   |-- convolution.py
|   |   |   |-- crop.py
|   |   |   |-- crop_and_resize.py
|   |   |   |-- deconvolution.py
|   |   |   |-- eltwise.py
|   |   |   |-- eltwise_unary.py
|   |   |   |-- elu.py
|   |   |   |-- embedding.py
|   |   |   |-- extract_glimpse.py
|   |   |   |-- fake_quant.py
|   |   |   |-- fill.py
|   |   |   |-- fullyconnected.py
|   |   |   |-- ignored_patterns.py
|   |   |   |-- image_projective_transform.py
|   |   |   |-- instance_norm.py
|   |   |   |-- lrn.py
|   |   |   |-- lstm.py
|   |   |   |-- non_max_suppression.py
|   |   |   |-- pad.py
|   |   |   |-- permute.py
|   |   |   |-- pixel_shuffle.py
|   |   |   |-- pooling.py
|   |   |   |-- pow.py
|   |   |   |-- prelu.py
|   |   |   |-- reduction.py
|   |   |   |-- relu.py
|   |   |   |-- relu6.py
|   |   |   |-- relu_min_max.py
|   |   |   |-- reshape.py
|   |   |   |-- resize.py
|   |   |   |-- sigmoid.py
|   |   |   |-- slice.py
|   |   |   |-- softmax.py
|   |   |   |-- ssd.py
|   |   |   |-- strided_slice.py
|   |   |   |-- tanh.py
|   |   |   `-- tile.py
|   |   |-- loader.py
|   |   |-- sequences
|   |   |   |-- __init__.py
|   |   |   |-- ignored.py
|   |   |   |-- lstm.py
|   |   |   `-- ssd.py
|   |   `-- util.py
|   `-- translation.py
`-- snpe
    |-- __init__.py
    |-- common
    |   |-- __init__.py
    |   |-- snpe_axis_transformer.py
    |   |-- snpe_converter_utils.py
    |   |-- snpe_udl_utils.py
    |   `-- snpe_validation_utils.py
    |-- snpe_caffe2_to_dlc.py
    |-- snpe_caffe_to_dlc.py
    |-- snpe_dlc_utils.py
    `-- snpe_utils.py

```

