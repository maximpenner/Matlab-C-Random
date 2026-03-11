classdef random_generator < handle
    properties (Access = private)
        seed (1,1) uint32
        x (1,1) uint32
        y (1,1) uint32
        z (1,1) uint32
        w (1,1) uint32
    end

    methods
        function obj = random_generator(seed)
            if nargin == 0
                obj.reset();
            else
                obj.set_seed(seed);
            end
        end

        function [] = reset(obj)
            arguments
                obj (1,1) lib_rand.random_generator
            end

            obj.set_seed(123456789);
        end

        function seed = get_seed(obj)
            seed = double(obj.seed);
        end

        function [] = set_seed(obj, seed)
            arguments
                obj (1,1) lib_rand.random_generator
                seed (1,1) double
            end

            assert(round(seed) == seed);
            assert(seed <= 2^32-1);

            obj.seed = uint32(seed);
            obj.x = uint32(seed);
            obj.y = uint32(1111111111);
            obj.z = uint32(2222222222);
            obj.w = uint32(3333333333);
        end

        function ret = rand(obj)
            arguments
                obj (1,1) lib_rand.random_generator
            end

            xor128(obj);
            ret = double(obj.w) / double(2^32-1);
        end

        function ret = randi(obj, min_val, max_val)
            arguments
                obj (1,1) lib_rand.random_generator
                min_val (1,1) double
                max_val (1,1) double
            end

            assert(min_val <= max_val);
            assert(min_val == round(min_val));
            assert(max_val == round(max_val));
            
            ret = floor(obj.rand() * (max_val - min_val + 1)) + min_val;
        end
    end

    methods (Access = private)
        function [] = xor128(obj)
            t = bitxor(obj.x, bitshift(obj.x,11));
            obj.x = obj.y;
            obj.y = obj.z;
            obj.z = obj.w;
            a = bitsra(obj.w,19);
            b = bitsra(t,8);
            c = bitxor(t,b);
            obj.w = bitxor(bitxor(obj.w,a),c);
        end
    end
end