#ifndef CAFFE_CUDNN_CONV_LAYER_HPP_
#define CAFFE_CUDNN_CONV_LAYER_HPP_

#include <vector>

#include "caffe/blob.hpp"
#include "caffe/layer.hpp"
#include "caffe/proto/caffe.pb.h"

#include "caffe/layers/operator/conv_layer.hpp"

namespace caffe {


template <typename Dtype>
class CuDNNConvolutionLayer : public ConvolutionLayer<Dtype> 
{
 public:
  explicit CuDNNConvolutionLayer(const LayerParameter& param) : ConvolutionLayer<Dtype>(param), handles_setup_(false) {}
  virtual ~CuDNNConvolutionLayer();
	virtual inline const char* type() const { return "CuDNNConvolution"; }

	virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top);
  virtual void Reshape(const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top);

  virtual void Forward_gpu(const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top);

  virtual void Backward_gpu(const vector<Blob<Dtype>*>& top,   const vector<Blob<Dtype>*>& bottom);
  virtual void SecForward_gpu(const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top);
 protected:
  

	
  bool handles_setup_;
  int gpu_id_;

	
  // algorithms for forward and backwards convolutions
  cudnnConvolutionFwdAlgo_t fwd_algo_;
  cudnnConvolutionBwdFilterAlgo_t bwd_filter_algo_;
  cudnnConvolutionBwdDataAlgo_t bwd_data_algo_;

  cudnnTensorDescriptor_t bottom_descs_, top_descs_;
  cudnnTensorDescriptor_t    bias_desc_;
  cudnnFilterDescriptor_t      filter_desc_;
  cudnnConvolutionDescriptor_t conv_descs_;
  int bottom_offset_, top_offset_, bias_offset_;

  size_t workspace_fwd_sizes_;
  size_t workspace_bwd_data_sizes_;
  size_t workspace_bwd_filter_sizes_;

	vector<Blob<Dtype> *> myworkspace_;
	
	int iter_;
	Blob<Dtype> v_blob_;
	Blob<Dtype> m_blob_;
	Blob<Dtype> buffer_blob_;
};


}  // namespace caffe

#endif  // CAFFE_CUDNN_CONV_LAYER_HPP_
