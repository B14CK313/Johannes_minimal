#include <memory>
#include <cstdio>
#include <optional>

struct Base {
	int i_;
	Base* parent_;

	Base(int i, Base* parent) : i_{i}, parent_{parent} {}

	virtual ~Base() = default;
	virtual std::optional<std::unique_ptr<Base>> f(int i) = 0;
};

struct DerivedInner : public Base {
	std::unique_ptr<Base> ptr_;

	explicit DerivedInner(int i, Base* parent) : Base(i, parent) {}
	~DerivedInner() override = default;

	std::optional<std::unique_ptr<Base>> f(int i) override {
		auto ret = ptr_->f(i);
		if(ret) ptr_ = std::move(*ret);
		return std::nullopt;
	}
};

struct DerivedLeaf : public Base {
	explicit DerivedLeaf(int i, Base* parent) : Base(i, parent) {}
	~DerivedLeaf() override = default;

	std::optional<std::unique_ptr<Base>> f(int i) override {
		if(i != i_) {
			auto ptr = std::make_unique<DerivedInner>(i_, parent_);
			ptr->ptr_ = std::make_unique<DerivedLeaf>(i, ptr.get());
			return std::optional{std::move(ptr)};
		}
		return std::nullopt;
	}
};

int main() {
	std::unique_ptr<Base> ptr = std::make_unique<DerivedLeaf>(42, nullptr);
	{
		printf("Addr. before:       %p\tVal. before:       %i\n", ptr.get(), ptr->i_);
		auto ret = ptr->f(42);
		if(ret) ptr = std::move(*ret);
		printf("Addr. after:        %p\tVal. after:        %i\n", ptr.get(), ptr->i_);
	}
	printf("\n");
	{
		printf("Addr. before:       %p\tVal. before:       %i\n", ptr.get(), ptr->i_);
		auto ret = ptr->f(11);
		if(ret) ptr = std::move(*ret);
		printf("Addr. after:        %p\tVal. after:        %i\n", ptr.get(), ptr->i_);
		printf("Addr. child after:  %p\tVal. child after:  %i\n", dynamic_cast<DerivedInner*>(ptr.get())->ptr_.get(),
		       dynamic_cast<DerivedInner*>(ptr.get())->ptr_->i_);
	}
}
