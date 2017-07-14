#include <vector>

#include "caffe/layers/operator/cudnn_batch_norm_layer.hpp"

namespace caffe {

template <typename Dtype>
void CuDNNBatchNormLayer<Dtype>::LayerSetUp(const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top)
{
	CUDA_CHECK(cudaGetDevice(&gpu_id_));
	int i;
	for (i=0;i<Caffe::GPUs.size();i++)
		if (Caffe::GPUs[i] == gpu_id_)
			break;
	gpu_id_ = i;
	
	mean_buffer_ = new Blob<Dtype>();
	var_buffer_ = new Blob<Dtype>();
	
  cudnn::createTensor4dDesc<Dtype>(&bottom_desc_);
  cudnn::createTensor4dDesc<Dtype>(&top_desc_);
  cudnn::createTensor4dDesc<Dtype>(&scale_bias_desc_);
  
  
  if (this->blobs_.size() == 4)
  	LOG(INFO)<<"skip initialization";
  else 
  {
    const int K = bottom[0]->channels();
    this->blobs_.resize(4);
    for(int i=0;i<this->blobs_.size();i++)
    {
      this->blobs_[i].reset(new Blob<Dtype>());
      this->blobs_[i]->Reshape(1,K,1,1);
    }
    Dtype std = 0.02;
    //caffe_rng_gaussian<Dtype>(this->blobs_[0]->count(), Dtype(1), std, this->blobs_[0]->mutable_cpu_data());
    //caffe_rng_gaussian<Dtype>(this->blobs_[1]->count(), Dtype(0), std, this->blobs_[1]->mutable_cpu_data());
    caffe_set(this->blobs_[0]->count(),Dtype(1),this->blobs_[0]->mutable_cpu_data());
    caffe_set(this->blobs_[1]->count(),Dtype(0),this->blobs_[1]->mutable_cpu_data());
    caffe_set(this->blobs_[2]->count(),Dtype(0),this->blobs_[2]->mutable_cpu_data());
    caffe_set(this->blobs_[3]->count(),Dtype(1),this->blobs_[3]->mutable_cpu_data());
		

		if (this->layer_param_.param_size() == 2)
	  { 
		  this->lr_mult().push_back(0);
		  this->decay_mult().push_back(0);
		  this->lr_mult().push_back(0);
		  this->decay_mult().push_back(0);
	  }	
		else if(this->layer_param_.param_size() == 0)
		{		
			this->lr_mult().push_back(1);
		  this->decay_mult().push_back(1);
		  this->lr_mult().push_back(1);
		  this->decay_mult().push_back(1);
		  this->lr_mult().push_back(0);
		  this->decay_mult().push_back(0);
		  this->lr_mult().push_back(0);
		  this->decay_mult().push_back(0);
		} 
  }

  
  is_initialize = false;
}

template <typename Dtype>
void CuDNNBatchNormLayer<Dtype>::Reshape(const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top)
{

  const int num = bottom[0]->num();
  const int channels = bottom[0]->channels();
  const int height = bottom[0]->height();
  const int width = bottom[0]->width();



  top[0]->Reshape(num,channels,height,width);    

	mean_buffer_->Reshape(1,channels,1,1);
  var_buffer_->Reshape(1,channels,1,1);

  cudnn::setTensor4dDesc<Dtype>(&bottom_desc_, num, channels, height, width);
  cudnn::setTensor4dDesc<Dtype>(&top_desc_, num, channels, height, width);
  cudnn::setTensor4dDesc<Dtype>(&scale_bias_desc_,  1, channels, 1, 1);

}

template <typename Dtype>
CuDNNBatchNormLayer<Dtype>::~CuDNNBatchNormLayer() 
{
	cudnnDestroyTensorDescriptor(bottom_desc_);
	cudnnDestroyTensorDescriptor(top_desc_);
	cudnnDestroyTensorDescriptor(scale_bias_desc_);
	
	delete mean_buffer_;
	delete var_buffer_;
}

INSTANTIATE_CLASS(CuDNNBatchNormLayer);
REGISTER_LAYER_CLASS(CuDNNBatchNorm);
}  // namespace caffe
