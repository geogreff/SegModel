#ifndef CAFFE_Imresize_LAYER_HPP_
#define CAFFE_Imresize_LAYER_HPP_

#include <vector>

#include "caffe/blob.hpp"
#include "caffe/layer.hpp"
#include "caffe/proto/caffe.pb.h"


namespace caffe {

template <typename Dtype>
class ImresizeLayer : public Layer<Dtype> {
 public:
  explicit ImresizeLayer(const LayerParameter& param): Layer<Dtype>(param) {}
  

  virtual inline const char* type() const { return "Imresize"; }
	
	virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top);
  virtual void Reshape(const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top);
  virtual void Forward_gpu(const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top);
  virtual void Backward_gpu(const vector<Blob<Dtype>*>& top, const vector<Blob<Dtype>*>& bottom);
  virtual void SecForward_gpu(const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top);
 protected:
 	int stride;
 	int kernel_size;
 	int num_classes;
};

}  // namespace caffe

#endif  // CAFFE_Imresize_LAYER_HPP_
		
